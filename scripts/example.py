from trex import transaction
from trex import agent
from trex import domains
from trex.utils import xml

class example_listener(transaction.reactor):
    "A simple reactor that post observations on sensor timeline"
    def __init__(self, me):
        "Basic constructor for trex reactor factory"
        transaction.reactor.__init__(self, me)
        # declare that it will use the timeline 'sensor' 
        self.use('sensor')
        # a dirty check that we succeeded - should throw an exception instead
        assert(self.is_external('sensor'))
    def notify(self,o):
        print 'Received', o.name, 'on', o.object, 'at', self.tick
        if o.has_attribute('temperature'):
            print '   -', o.attribute('temperature')
    def synchronize(self):        
        # even if empty always implent this method
        # also returning False implies the reactor death 
        return True


class example_publisher(transaction.reactor):
    "A simple reactor that post observations on sensor timeline"
    def __init__(self, me):
        "Basic constructor for trex reactor factory"
        transaction.reactor.__init__(self, me)
        # declare that it will own the timeline 'sensor' 
        self.provide('sensor')
        # a dirty check that we succeeded - should throw an exception instead
        assert(self.is_internal('sensor'))
        # set the timeline value to some default 'undefined' predicate
        self.post(transaction.obs('sensor', 'undefined'))
    def synchronize(self):        
        # print 'create a new observation named Value on sensor'
        o = transaction.obs('sensor', 'Value');
        # print 'add attribute float temperature=12.5'
        o.restrict(domains.var('temperature', domains.float(12.5)));
        # print 'add attribute bool test=True'
        o.restrict(domains.var('test', domains.bool(True)));
        # print 'add attribute int int_interval=[5, 10]'
        o.restrict(domains.var('int_interval', domains.int(5, 10)));
        # uncomment this to test exceptions: should work just need more exception types
        #try:
        #    o.restrict(domains.var('int_interval', domains.int(11, 20)));
        #except domains.empty_domain as err:
        #    self.warning("Captured expected exception: {}".format(err))

        # if tick is a ,multiple of 3 then post nothing
        if self.tick%3>0:
            # post this observation at any tick that is not divisible by 3
            self.post(o)
            if self.tick%2==0:
                    # post multiple observation on even tick numbers
                    #  only the last one will be seen by trex
                    self.post(transaction.obs('sensor', 'Even'));
        return True


if __name__ == "__main__":
    import trex
    import signal
    import sys

    # # Properly handling a ^C allow to more csmoothly stop trex
    # def signal_handler(signal, frame):
    #     # ideally I should send some stop event to TREX
    #     sys.exit(0)
        
    # signal.signal(signal.SIGINT, signal_handler)

    print('Trex version {}'.format(trex.version.str))
    # Now a simple way to create an agent and inject this new reactor in it

    # First I need to make sure that I have the logging system active
    # this is required to do as it also create the threads used for trex execution
    pylog = trex.utils.log('python');
    # the log directory is always symbolically linked to $TREX_LOG_DIR/latest
    #   its name is $TREX_LOG_DIR/YYYY.DDD.NN
    #    with YYYY being the year
    #         DDD being the day of year
    #         NN being a two digit number that increase with each new run in the day
    print 'Log messages will be produced in ', pylog.dir
    # pylog.info('Does this message appear in latest/TREX.log ? YES')

    # here I define a simple xml config for trex that declares the 2 reactors
    # in an agent named python_example
    cfg = xml.from_str('<Agent name="python_example" finalTick="200">'
                       '   <PyReactor name="foo" python_class="example_publisher"'
                       ' lookahead="0" latency="0"/>'
                       '   <PyReactor name="bar" python_class="example_listener"'
                       ' lookahead="0" latency="0"/>'
                       '</Agent>');

    #help(example_reactor)
    print 'Loading agent defined as:', cfg
    my_agent = agent.agent(iter(cfg).next());


    
    print 'Creating clock';
    # create the reactor clock updating tick every 500ms (2Hz)
    clk = agent.rt_clock(500)
    print 'Clock created: {}'.format(clk);
    
    # attach this clock to my agent
    if not my_agent.set_clock(clk):
        print('Agent {} already had a clock'.format(my_agent.name))
    print 'Running the agent ', my_agent.name, ' with final tick at ', my_agent.final_tick
    # run the agent
    my_agent.run()

    


### Note for ROS integration: this code extract attributes of a class or instance 'x'
# filter(lambda attr: not (attr.startswith('_') or callable(getattr(x, attr))), dir(x))
