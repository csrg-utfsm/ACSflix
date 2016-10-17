// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: BdFileBlock.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "BdFileBlock.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* BdFileBlock_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  BdFileBlock_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_BdFileBlock_2eproto() {
  protobuf_AddDesc_BdFileBlock_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "BdFileBlock.proto");
  GOOGLE_CHECK(file != NULL);
  BdFileBlock_descriptor_ = file->message_type(0);
  static const int BdFileBlock_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BdFileBlock, offset_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BdFileBlock, data_),
  };
  BdFileBlock_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      BdFileBlock_descriptor_,
      BdFileBlock::default_instance_,
      BdFileBlock_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BdFileBlock, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BdFileBlock, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(BdFileBlock));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_BdFileBlock_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    BdFileBlock_descriptor_, &BdFileBlock::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_BdFileBlock_2eproto() {
  delete BdFileBlock::default_instance_;
  delete BdFileBlock_reflection_;
}

void protobuf_AddDesc_BdFileBlock_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\021BdFileBlock.proto\"+\n\013BdFileBlock\022\016\n\006of"
    "fset\030\001 \002(\004\022\014\n\004data\030\002 \002(\014", 64);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "BdFileBlock.proto", &protobuf_RegisterTypes);
  BdFileBlock::default_instance_ = new BdFileBlock();
  BdFileBlock::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_BdFileBlock_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_BdFileBlock_2eproto {
  StaticDescriptorInitializer_BdFileBlock_2eproto() {
    protobuf_AddDesc_BdFileBlock_2eproto();
  }
} static_descriptor_initializer_BdFileBlock_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int BdFileBlock::kOffsetFieldNumber;
const int BdFileBlock::kDataFieldNumber;
#endif  // !_MSC_VER

BdFileBlock::BdFileBlock()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void BdFileBlock::InitAsDefaultInstance() {
}

BdFileBlock::BdFileBlock(const BdFileBlock& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void BdFileBlock::SharedCtor() {
  _cached_size_ = 0;
  offset_ = GOOGLE_ULONGLONG(0);
  data_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

BdFileBlock::~BdFileBlock() {
  SharedDtor();
}

void BdFileBlock::SharedDtor() {
  if (data_ != &::google::protobuf::internal::kEmptyString) {
    delete data_;
  }
  if (this != default_instance_) {
  }
}

void BdFileBlock::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* BdFileBlock::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return BdFileBlock_descriptor_;
}

const BdFileBlock& BdFileBlock::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_BdFileBlock_2eproto();
  return *default_instance_;
}

BdFileBlock* BdFileBlock::default_instance_ = NULL;

BdFileBlock* BdFileBlock::New() const {
  return new BdFileBlock;
}

void BdFileBlock::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    offset_ = GOOGLE_ULONGLONG(0);
    if (has_data()) {
      if (data_ != &::google::protobuf::internal::kEmptyString) {
        data_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool BdFileBlock::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint64 offset = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &offset_)));
          set_has_offset();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_data;
        break;
      }

      // required bytes data = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_data:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_data()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void BdFileBlock::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint64 offset = 1;
  if (has_offset()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(1, this->offset(), output);
  }

  // required bytes data = 2;
  if (has_data()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytes(
      2, this->data(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* BdFileBlock::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint64 offset = 1;
  if (has_offset()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(1, this->offset(), target);
  }

  // required bytes data = 2;
  if (has_data()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        2, this->data(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int BdFileBlock::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint64 offset = 1;
    if (has_offset()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt64Size(
          this->offset());
    }

    // required bytes data = 2;
    if (has_data()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->data());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void BdFileBlock::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const BdFileBlock* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const BdFileBlock*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void BdFileBlock::MergeFrom(const BdFileBlock& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_offset()) {
      set_offset(from.offset());
    }
    if (from.has_data()) {
      set_data(from.data());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void BdFileBlock::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void BdFileBlock::CopyFrom(const BdFileBlock& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool BdFileBlock::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void BdFileBlock::Swap(BdFileBlock* other) {
  if (other != this) {
    std::swap(offset_, other->offset_);
    std::swap(data_, other->data_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata BdFileBlock::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = BdFileBlock_descriptor_;
  metadata.reflection = BdFileBlock_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
