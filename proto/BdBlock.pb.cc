// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: BdBlock.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "BdBlock.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* BdBlock_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  BdBlock_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_BdBlock_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_BdBlock_2eproto() {
  protobuf_AddDesc_BdBlock_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "BdBlock.proto");
  GOOGLE_CHECK(file != NULL);
  BdBlock_descriptor_ = file->message_type(0);
  static const int BdBlock_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BdBlock, offset_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BdBlock, message_),
  };
  BdBlock_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      BdBlock_descriptor_,
      BdBlock::internal_default_instance(),
      BdBlock_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BdBlock, _has_bits_),
      -1,
      -1,
      sizeof(BdBlock),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BdBlock, _internal_metadata_));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_BdBlock_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      BdBlock_descriptor_, BdBlock::internal_default_instance());
}

}  // namespace

void protobuf_ShutdownFile_BdBlock_2eproto() {
  BdBlock_default_instance_.Shutdown();
  delete BdBlock_reflection_;
}

void protobuf_InitDefaults_BdBlock_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::GetEmptyString();
  BdBlock_default_instance_.DefaultConstruct();
  BdBlock_default_instance_.get_mutable()->InitAsDefaultInstance();
}

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_InitDefaults_BdBlock_2eproto_once_);
void protobuf_InitDefaults_BdBlock_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_InitDefaults_BdBlock_2eproto_once_,
                 &protobuf_InitDefaults_BdBlock_2eproto_impl);
}
void protobuf_AddDesc_BdBlock_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  protobuf_InitDefaults_BdBlock_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\rBdBlock.proto\"*\n\007BdBlock\022\016\n\006offset\030\001 \002"
    "(\r\022\017\n\007message\030\002 \002(\t", 59);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "BdBlock.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_BdBlock_2eproto);
}

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_BdBlock_2eproto_once_);
void protobuf_AddDesc_BdBlock_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_BdBlock_2eproto_once_,
                 &protobuf_AddDesc_BdBlock_2eproto_impl);
}
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_BdBlock_2eproto {
  StaticDescriptorInitializer_BdBlock_2eproto() {
    protobuf_AddDesc_BdBlock_2eproto();
  }
} static_descriptor_initializer_BdBlock_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD GOOGLE_ATTRIBUTE_NORETURN;
static void MergeFromFail(int line) {
  ::google::protobuf::internal::MergeFromFail(__FILE__, line);
}

}  // namespace


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int BdBlock::kOffsetFieldNumber;
const int BdBlock::kMessageFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

BdBlock::BdBlock()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (this != internal_default_instance()) protobuf_InitDefaults_BdBlock_2eproto();
  SharedCtor();
  // @@protoc_insertion_point(constructor:BdBlock)
}

void BdBlock::InitAsDefaultInstance() {
}

BdBlock::BdBlock(const BdBlock& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  UnsafeMergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:BdBlock)
}

void BdBlock::SharedCtor() {
  _cached_size_ = 0;
  message_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  offset_ = 0u;
}

BdBlock::~BdBlock() {
  // @@protoc_insertion_point(destructor:BdBlock)
  SharedDtor();
}

void BdBlock::SharedDtor() {
  message_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void BdBlock::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* BdBlock::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return BdBlock_descriptor_;
}

const BdBlock& BdBlock::default_instance() {
  protobuf_InitDefaults_BdBlock_2eproto();
  return *internal_default_instance();
}

::google::protobuf::internal::ExplicitlyConstructed<BdBlock> BdBlock_default_instance_;

BdBlock* BdBlock::New(::google::protobuf::Arena* arena) const {
  BdBlock* n = new BdBlock;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void BdBlock::Clear() {
// @@protoc_insertion_point(message_clear_start:BdBlock)
  if (_has_bits_[0 / 32] & 3u) {
    offset_ = 0u;
    if (has_message()) {
      message_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }
  }
  _has_bits_.Clear();
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool BdBlock::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:BdBlock)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 offset = 1;
      case 1: {
        if (tag == 8) {
          set_has_offset();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &offset_)));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_message;
        break;
      }

      // required string message = 2;
      case 2: {
        if (tag == 18) {
         parse_message:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_message()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->message().data(), this->message().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "BdBlock.message");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:BdBlock)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:BdBlock)
  return false;
#undef DO_
}

void BdBlock::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:BdBlock)
  // required uint32 offset = 1;
  if (has_offset()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->offset(), output);
  }

  // required string message = 2;
  if (has_message()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->message().data(), this->message().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "BdBlock.message");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->message(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:BdBlock)
}

::google::protobuf::uint8* BdBlock::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:BdBlock)
  // required uint32 offset = 1;
  if (has_offset()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->offset(), target);
  }

  // required string message = 2;
  if (has_message()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->message().data(), this->message().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "BdBlock.message");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->message(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:BdBlock)
  return target;
}

size_t BdBlock::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:BdBlock)
  size_t total_size = 0;

  if (has_offset()) {
    // required uint32 offset = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->offset());
  }

  if (has_message()) {
    // required string message = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->message());
  }

  return total_size;
}
size_t BdBlock::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:BdBlock)
  size_t total_size = 0;

  if (((_has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required uint32 offset = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->offset());

    // required string message = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->message());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void BdBlock::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:BdBlock)
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const BdBlock* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const BdBlock>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:BdBlock)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:BdBlock)
    UnsafeMergeFrom(*source);
  }
}

void BdBlock::MergeFrom(const BdBlock& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:BdBlock)
  if (GOOGLE_PREDICT_TRUE(&from != this)) {
    UnsafeMergeFrom(from);
  } else {
    MergeFromFail(__LINE__);
  }
}

void BdBlock::UnsafeMergeFrom(const BdBlock& from) {
  GOOGLE_DCHECK(&from != this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_offset()) {
      set_offset(from.offset());
    }
    if (from.has_message()) {
      set_has_message();
      message_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.message_);
    }
  }
  if (from._internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::UnknownFieldSet::MergeToInternalMetdata(
      from.unknown_fields(), &_internal_metadata_);
  }
}

void BdBlock::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:BdBlock)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void BdBlock::CopyFrom(const BdBlock& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:BdBlock)
  if (&from == this) return;
  Clear();
  UnsafeMergeFrom(from);
}

bool BdBlock::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void BdBlock::Swap(BdBlock* other) {
  if (other == this) return;
  InternalSwap(other);
}
void BdBlock::InternalSwap(BdBlock* other) {
  std::swap(offset_, other->offset_);
  message_.Swap(&other->message_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata BdBlock::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = BdBlock_descriptor_;
  metadata.reflection = BdBlock_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// BdBlock

// required uint32 offset = 1;
bool BdBlock::has_offset() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void BdBlock::set_has_offset() {
  _has_bits_[0] |= 0x00000001u;
}
void BdBlock::clear_has_offset() {
  _has_bits_[0] &= ~0x00000001u;
}
void BdBlock::clear_offset() {
  offset_ = 0u;
  clear_has_offset();
}
::google::protobuf::uint32 BdBlock::offset() const {
  // @@protoc_insertion_point(field_get:BdBlock.offset)
  return offset_;
}
void BdBlock::set_offset(::google::protobuf::uint32 value) {
  set_has_offset();
  offset_ = value;
  // @@protoc_insertion_point(field_set:BdBlock.offset)
}

// required string message = 2;
bool BdBlock::has_message() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void BdBlock::set_has_message() {
  _has_bits_[0] |= 0x00000002u;
}
void BdBlock::clear_has_message() {
  _has_bits_[0] &= ~0x00000002u;
}
void BdBlock::clear_message() {
  message_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_message();
}
const ::std::string& BdBlock::message() const {
  // @@protoc_insertion_point(field_get:BdBlock.message)
  return message_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void BdBlock::set_message(const ::std::string& value) {
  set_has_message();
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:BdBlock.message)
}
void BdBlock::set_message(const char* value) {
  set_has_message();
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:BdBlock.message)
}
void BdBlock::set_message(const char* value, size_t size) {
  set_has_message();
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:BdBlock.message)
}
::std::string* BdBlock::mutable_message() {
  set_has_message();
  // @@protoc_insertion_point(field_mutable:BdBlock.message)
  return message_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* BdBlock::release_message() {
  // @@protoc_insertion_point(field_release:BdBlock.message)
  clear_has_message();
  return message_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void BdBlock::set_allocated_message(::std::string* message) {
  if (message != NULL) {
    set_has_message();
  } else {
    clear_has_message();
  }
  message_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), message);
  // @@protoc_insertion_point(field_set_allocated:BdBlock.message)
}

inline const BdBlock* BdBlock::internal_default_instance() {
  return &BdBlock_default_instance_.get();
}
#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)