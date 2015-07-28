/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2015, Frederic Py.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the TREX Project nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef H_trex_ros_pyros_reactor
# define H_trex_ros_pyros_reactor

# include <trex/transaction/TeleoReactor.hh>
# include <trex/python/python_env.hh>
# include <trex/python/exception_helper.hh>
# include "roscpp_inject.hh"
# include "trex/ros/bits/ros_timeline.hh"


namespace TREX {
  namespace ROS {
    
    class ros_reactor :public transaction::TeleoReactor {
    public:
      typedef details::ros_timeline::xml_factory tl_factory;

      ros_reactor(transaction::TeleoReactor::xml_arg_type arg);
      ~ros_reactor();
      
      boost::python::object &rospy() {
        return m_ros->rospy();
      }
      

    private:
      utils::SingletonUse<tl_factory> m_factory;
      
      void handleInit();
      bool synchronize();
      
      utils::SingletonUse<roscpp_initializer>  m_ros;
      typedef utils::list_set<details::ros_timeline> tl_set;
      tl_set m_timelines;
      
      friend class details::ros_timeline;
    };
    
  }
}

#endif // H_trex_ros_pyros_reactor