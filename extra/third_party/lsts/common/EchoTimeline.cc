/*
 * EchoTimeline.cpp
 *
 *  Created on: Mar 27, 2014
 *      Author: zp
 */

#include "EchoTimeline.hh"
using namespace TREX::LSTS;
using namespace TREX::transaction;
using namespace TREX::utils;

namespace
{
  /** @brief EchoTimeline reactor declaration */
  reactor::declare<EchoTimeline> decl("EchoTimeline");
}

namespace TREX
{
  namespace LSTS
  {
    // constructor
    EchoTimeline::EchoTimeline(TREX::transaction::reactor::xml_arg_type arg):
        LstsReactor(arg)
    {
      m_timeline = parse_attr<std::string>("params", xml(arg),
                                             "timeline");

      m_initial_state = parse_attr<std::string>("Boot", xml(arg),
                                           "initial");
      m_first_tick = true;
    }

    void
    EchoTimeline::handle_init()
    {
      provide(m_timeline, true, false);
    }

    // called each tick
    bool
    EchoTimeline::synchronize()
    {
      if (m_first_tick)
      {
        postUniqueObservation(token(m_timeline, m_initial_state));
      }
      m_first_tick = false;
      return true;
    }

    // called when a goal is requested
    void
    EchoTimeline::handle_request(token_id const &g)
    {
      if (g.get()->object().str() == m_timeline)
      {
        TREX::transaction::token observation(*g);
        postUniqueObservation(observation);
      }
      else
      {
        syslog(log::warn) << "Cannot handle requests on " << g.get()->object().str();
        return;
      }
    }

    // destructor
    EchoTimeline::~EchoTimeline()
    {
      // TODO Auto-generated destructor stub
    }

  } /* namespace Fragments */
} /* namespace Transports */
