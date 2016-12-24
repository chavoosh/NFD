/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2014-2016,  Regents of the University of California,
 *                           Arizona Board of Regents,
 *                           Colorado State University,
 *                           University Pierre & Marie Curie, Sorbonne University,
 *                           Washington University in St. Louis,
 *                           Beijing Institute of Technology,
 *                           The University of Memphis.
 *
 * This file is part of NFD (Named Data Networking Forwarding Daemon).
 * See AUTHORS.md for complete list of NFD authors and contributors.
 *
 * NFD is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * NFD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * NFD, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "fw/client-control-strategy.hpp"

#include "tests/test-common.hpp"

namespace nfd {
namespace fw {
namespace tests {

using namespace nfd::tests;

BOOST_AUTO_TEST_SUITE(Fw)
BOOST_FIXTURE_TEST_SUITE(TestClientControlStrategy, BaseFixture)

BOOST_AUTO_TEST_CASE(Registration)
{
  BOOST_CHECK_EQUAL(Strategy::listRegistered().count(ClientControlStrategy::getStrategyName()), 1);
}

BOOST_AUTO_TEST_CASE(InstanceName)
{
  Forwarder forwarder;
  BOOST_REQUIRE(ClientControlStrategy::getStrategyName().at(-1).isVersion());
  BOOST_CHECK_EQUAL(
    ClientControlStrategy(forwarder, ClientControlStrategy::getStrategyName().getPrefix(-1)).getInstanceName(),
    ClientControlStrategy::getStrategyName());
  BOOST_CHECK_THROW(
    ClientControlStrategy(forwarder, Name(ClientControlStrategy::getStrategyName()).append("param")),
    std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END() // TestClientControlStrategy
BOOST_AUTO_TEST_SUITE_END() // Fw

} // namespace tests
} // namespace fw
} // namespace nfd