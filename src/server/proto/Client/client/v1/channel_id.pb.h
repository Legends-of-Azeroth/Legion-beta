/*
 *###############################################################################
 *#                                                                             #
 *# Copyright (C) 2022 Project Nighthold <https://github.com/ProjectNighthold>  #
 *#                                                                             #
 *# This file is free software; as a special exception the author gives         #
 *# unlimited permission to copy and/or distribute it, with or without          #
 *# modifications, as long as this notice is preserved.                         #
 *#                                                                             #
 *# This program is distributed in the hope that it will be useful, but         #
 *# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      #
 *# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    #
 *#                                                                             #
 *# Read the THANKS file on the source root directory for more info.            #
 *#                                                                             #
 *###############################################################################
 */

#ifndef PROTOBUF_client_2fv1_2fchannel_5fid_2eproto__INCLUDED
#define PROTOBUF_client_2fv1_2fchannel_5fid_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
#include "rpc_types.pb.h"
#include "Define.h" // for TC_PROTO_API
// @@protoc_insertion_point(includes)

namespace bgs {
namespace protocol {
namespace channel {
namespace v1 {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_client_2fv1_2fchannel_5fid_2eproto();
void protobuf_AssignDesc_client_2fv1_2fchannel_5fid_2eproto();
void protobuf_ShutdownFile_client_2fv1_2fchannel_5fid_2eproto();

class ChannelId;

// ===================================================================

class ChannelId : public ::google::protobuf::Message {
 public:
  ChannelId();
  virtual ~ChannelId();

  ChannelId(const ChannelId& from);

  inline ChannelId& operator=(const ChannelId& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ChannelId& default_instance();

  void Swap(ChannelId* other);

  // implements Message ----------------------------------------------

  ChannelId* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ChannelId& from);
  void MergeFrom(const ChannelId& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional uint32 type = 1;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline ::google::protobuf::uint32 type() const;
  inline void set_type(::google::protobuf::uint32 value);

  // optional .bgs.protocol.ProcessId host = 2;
  inline bool has_host() const;
  inline void clear_host();
  static const int kHostFieldNumber = 2;
  inline const ::bgs::protocol::ProcessId& host() const;
  inline ::bgs::protocol::ProcessId* mutable_host();
  inline ::bgs::protocol::ProcessId* release_host();
  inline void set_allocated_host(::bgs::protocol::ProcessId* host);

  // optional fixed32 id = 3;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 3;
  inline ::google::protobuf::uint32 id() const;
  inline void set_id(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:bgs.protocol.channel.v1.ChannelId)
 private:
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_host();
  inline void clear_has_host();
  inline void set_has_id();
  inline void clear_has_id();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::bgs::protocol::ProcessId* host_;
  ::google::protobuf::uint32 type_;
  ::google::protobuf::uint32 id_;
  friend void protobuf_AddDesc_client_2fv1_2fchannel_5fid_2eproto();
  friend void protobuf_AssignDesc_client_2fv1_2fchannel_5fid_2eproto();
  friend void protobuf_ShutdownFile_client_2fv1_2fchannel_5fid_2eproto();

  void InitAsDefaultInstance();
  static ChannelId* default_instance_;
};
// ===================================================================


// ===================================================================


// ===================================================================

// ChannelId

// optional uint32 type = 1;
inline bool ChannelId::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ChannelId::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ChannelId::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ChannelId::clear_type() {
  type_ = 0u;
  clear_has_type();
}
inline ::google::protobuf::uint32 ChannelId::type() const {
  // @@protoc_insertion_point(field_get:bgs.protocol.channel.v1.ChannelId.type)
  return type_;
}
inline void ChannelId::set_type(::google::protobuf::uint32 value) {
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:bgs.protocol.channel.v1.ChannelId.type)
}

// optional .bgs.protocol.ProcessId host = 2;
inline bool ChannelId::has_host() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ChannelId::set_has_host() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ChannelId::clear_has_host() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ChannelId::clear_host() {
  if (host_ != NULL) host_->::bgs::protocol::ProcessId::Clear();
  clear_has_host();
}
inline const ::bgs::protocol::ProcessId& ChannelId::host() const {
  // @@protoc_insertion_point(field_get:bgs.protocol.channel.v1.ChannelId.host)
  return host_ != NULL ? *host_ : *default_instance_->host_;
}
inline ::bgs::protocol::ProcessId* ChannelId::mutable_host() {
  set_has_host();
  if (host_ == NULL) host_ = new ::bgs::protocol::ProcessId;
  // @@protoc_insertion_point(field_mutable:bgs.protocol.channel.v1.ChannelId.host)
  return host_;
}
inline ::bgs::protocol::ProcessId* ChannelId::release_host() {
  clear_has_host();
  ::bgs::protocol::ProcessId* temp = host_;
  host_ = NULL;
  return temp;
}
inline void ChannelId::set_allocated_host(::bgs::protocol::ProcessId* host) {
  delete host_;
  host_ = host;
  if (host) {
    set_has_host();
  } else {
    clear_has_host();
  }
  // @@protoc_insertion_point(field_set_allocated:bgs.protocol.channel.v1.ChannelId.host)
}

// optional fixed32 id = 3;
inline bool ChannelId::has_id() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ChannelId::set_has_id() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ChannelId::clear_has_id() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ChannelId::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 ChannelId::id() const {
  // @@protoc_insertion_point(field_get:bgs.protocol.channel.v1.ChannelId.id)
  return id_;
}
inline void ChannelId::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:bgs.protocol.channel.v1.ChannelId.id)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace v1
}  // namespace channel
}  // namespace protocol
}  // namespace bgs

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_client_2fv1_2fchannel_5fid_2eproto__INCLUDED