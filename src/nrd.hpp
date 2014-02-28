/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (C) 2014 Named Data Networking Project
 * See COPYING for copyright and distribution information.
 */

#ifndef NRD_HPP
#define NRD_HPP

#include "rib.hpp"

namespace ndn {
namespace nrd {

class Nrd
{
public:
  Nrd();

  void
  onRibRequest(const Interest& request);

  void
  enableLocalControlHeader();

  void
  listen();

private:
  void
  sendResponse(const Name& name,
               const nfd::ControlResponse& response);

  void
  sendResponse(const Name& name,
               uint32_t code,
               const std::string& text);
  void
  onCommandError(const std::string& error, 
                 const ndn::Interest& interest, 
                 const PrefixRegOptions& options);
 
  void
  onRegSuccess(const ndn::Interest& interest, const PrefixRegOptions& options);

  void
  onUnRegSuccess(const ndn::Interest& interest, const PrefixRegOptions& options);

  void
  onControlHeaderSuccess();

  void
  onControlHeaderError();

  void
  insertEntry(const Interest& request, const PrefixRegOptions& options);

  void
  deleteEntry(const Interest& request, const PrefixRegOptions& options);

  bool
  extractOptions(const Interest& request,
                 PrefixRegOptions& extractedOptions);
private:
  Rib m_managedRib;
  ndn::Face m_face;
  ndn::KeyChain m_keyChain;
  shared_ptr<nfd::Controller> m_nfdController;

  typedef boost::function<void(Nrd*,
                               const Interest&,
                               const PrefixRegOptions&)> VerbProcessor;

  typedef std::map<Name::Component, VerbProcessor> VerbDispatchTable;

  typedef std::pair<Name::Component, VerbProcessor> VerbAndProcessor;


  const VerbDispatchTable m_verbDispatch;

  static const Name COMMAND_PREFIX; // /localhost/nrd

  // number of components in an invalid, but not malformed, unsigned command.
  // (/localhost/nrd + verb + options) = 4
  static const size_t COMMAND_UNSIGNED_NCOMPS;

  // number of components in a valid signed Interest.
  // 5 in mock (see UNSIGNED_NCOMPS), 8 with signed Interest support.
  static const size_t COMMAND_SIGNED_NCOMPS;

  static const VerbAndProcessor COMMAND_VERBS[];
};

} // namespace nrd
} // namespace ndn

#endif // NRD_HPP

