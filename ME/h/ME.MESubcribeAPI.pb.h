// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ME.MESubcribeAPI.proto

#ifndef PROTOBUF_ME_2eMESubcribeAPI_2eproto__INCLUDED
#define PROTOBUF_ME_2eMESubcribeAPI_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3005001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace protobuf_ME_2eMESubcribeAPI_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[3];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
void InitDefaultsST_TRANS_ORDER_INFOImpl();
void InitDefaultsST_TRANS_ORDER_INFO();
void InitDefaultsST_MART_QUOTATIONImpl();
void InitDefaultsST_MART_QUOTATION();
void InitDefaultsST_REP_TRANS_ORDER_REQUESTImpl();
void InitDefaultsST_REP_TRANS_ORDER_REQUEST();
inline void InitDefaults() {
  InitDefaultsST_TRANS_ORDER_INFO();
  InitDefaultsST_MART_QUOTATION();
  InitDefaultsST_REP_TRANS_ORDER_REQUEST();
}
}  // namespace protobuf_ME_2eMESubcribeAPI_2eproto
namespace MESubcribeAPI {
class ST_MART_QUOTATION;
class ST_MART_QUOTATIONDefaultTypeInternal;
extern ST_MART_QUOTATIONDefaultTypeInternal _ST_MART_QUOTATION_default_instance_;
class ST_REP_TRANS_ORDER_REQUEST;
class ST_REP_TRANS_ORDER_REQUESTDefaultTypeInternal;
extern ST_REP_TRANS_ORDER_REQUESTDefaultTypeInternal _ST_REP_TRANS_ORDER_REQUEST_default_instance_;
class ST_TRANS_ORDER_INFO;
class ST_TRANS_ORDER_INFODefaultTypeInternal;
extern ST_TRANS_ORDER_INFODefaultTypeInternal _ST_TRANS_ORDER_INFO_default_instance_;
}  // namespace MESubcribeAPI
namespace MESubcribeAPI {

// ===================================================================

class ST_TRANS_ORDER_INFO : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:MESubcribeAPI.ST_TRANS_ORDER_INFO) */ {
 public:
  ST_TRANS_ORDER_INFO();
  virtual ~ST_TRANS_ORDER_INFO();

  ST_TRANS_ORDER_INFO(const ST_TRANS_ORDER_INFO& from);

  inline ST_TRANS_ORDER_INFO& operator=(const ST_TRANS_ORDER_INFO& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  ST_TRANS_ORDER_INFO(ST_TRANS_ORDER_INFO&& from) noexcept
    : ST_TRANS_ORDER_INFO() {
    *this = ::std::move(from);
  }

  inline ST_TRANS_ORDER_INFO& operator=(ST_TRANS_ORDER_INFO&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const ST_TRANS_ORDER_INFO& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ST_TRANS_ORDER_INFO* internal_default_instance() {
    return reinterpret_cast<const ST_TRANS_ORDER_INFO*>(
               &_ST_TRANS_ORDER_INFO_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(ST_TRANS_ORDER_INFO* other);
  friend void swap(ST_TRANS_ORDER_INFO& a, ST_TRANS_ORDER_INFO& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline ST_TRANS_ORDER_INFO* New() const PROTOBUF_FINAL { return New(NULL); }

  ST_TRANS_ORDER_INFO* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const ST_TRANS_ORDER_INFO& from);
  void MergeFrom(const ST_TRANS_ORDER_INFO& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(ST_TRANS_ORDER_INFO* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string strBidOrderID = 1;
  void clear_strbidorderid();
  static const int kStrBidOrderIDFieldNumber = 1;
  const ::std::string& strbidorderid() const;
  void set_strbidorderid(const ::std::string& value);
  #if LANG_CXX11
  void set_strbidorderid(::std::string&& value);
  #endif
  void set_strbidorderid(const char* value);
  void set_strbidorderid(const char* value, size_t size);
  ::std::string* mutable_strbidorderid();
  ::std::string* release_strbidorderid();
  void set_allocated_strbidorderid(::std::string* strbidorderid);

  // string strAskOrderID = 2;
  void clear_straskorderid();
  static const int kStrAskOrderIDFieldNumber = 2;
  const ::std::string& straskorderid() const;
  void set_straskorderid(const ::std::string& value);
  #if LANG_CXX11
  void set_straskorderid(::std::string&& value);
  #endif
  void set_straskorderid(const char* value);
  void set_straskorderid(const char* value, size_t size);
  ::std::string* mutable_straskorderid();
  ::std::string* release_straskorderid();
  void set_allocated_straskorderid(::std::string* straskorderid);

  // uint32 uiBidUserID = 3;
  void clear_uibiduserid();
  static const int kUiBidUserIDFieldNumber = 3;
  ::google::protobuf::uint32 uibiduserid() const;
  void set_uibiduserid(::google::protobuf::uint32 value);

  // uint32 uiAskUserID = 4;
  void clear_uiaskuserid();
  static const int kUiAskUserIDFieldNumber = 4;
  ::google::protobuf::uint32 uiaskuserid() const;
  void set_uiaskuserid(::google::protobuf::uint32 value);

  // int64 fPrice = 5;
  void clear_fprice();
  static const int kFPriceFieldNumber = 5;
  ::google::protobuf::int64 fprice() const;
  void set_fprice(::google::protobuf::int64 value);

  // int64 fNumber = 6;
  void clear_fnumber();
  static const int kFNumberFieldNumber = 6;
  ::google::protobuf::int64 fnumber() const;
  void set_fnumber(::google::protobuf::int64 value);

  // uint64 ucRecordID = 8;
  void clear_ucrecordid();
  static const int kUcRecordIDFieldNumber = 8;
  ::google::protobuf::uint64 ucrecordid() const;
  void set_ucrecordid(::google::protobuf::uint64 value);

  // uint32 ucExchType = 7;
  void clear_ucexchtype();
  static const int kUcExchTypeFieldNumber = 7;
  ::google::protobuf::uint32 ucexchtype() const;
  void set_ucexchtype(::google::protobuf::uint32 value);

  // uint32 ucOrderStatus = 9;
  void clear_ucorderstatus();
  static const int kUcOrderStatusFieldNumber = 9;
  ::google::protobuf::uint32 ucorderstatus() const;
  void set_ucorderstatus(::google::protobuf::uint32 value);

  // uint64 meBidOrderID = 11;
  void clear_mebidorderid();
  static const int kMeBidOrderIDFieldNumber = 11;
  ::google::protobuf::uint64 mebidorderid() const;
  void set_mebidorderid(::google::protobuf::uint64 value);

  // uint64 meAskOrderID = 12;
  void clear_measkorderid();
  static const int kMeAskOrderIDFieldNumber = 12;
  ::google::protobuf::uint64 measkorderid() const;
  void set_measkorderid(::google::protobuf::uint64 value);

  // uint32 uiExchObjID = 10;
  void clear_uiexchobjid();
  static const int kUiExchObjIDFieldNumber = 10;
  ::google::protobuf::uint32 uiexchobjid() const;
  void set_uiexchobjid(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:MESubcribeAPI.ST_TRANS_ORDER_INFO)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr strbidorderid_;
  ::google::protobuf::internal::ArenaStringPtr straskorderid_;
  ::google::protobuf::uint32 uibiduserid_;
  ::google::protobuf::uint32 uiaskuserid_;
  ::google::protobuf::int64 fprice_;
  ::google::protobuf::int64 fnumber_;
  ::google::protobuf::uint64 ucrecordid_;
  ::google::protobuf::uint32 ucexchtype_;
  ::google::protobuf::uint32 ucorderstatus_;
  ::google::protobuf::uint64 mebidorderid_;
  ::google::protobuf::uint64 measkorderid_;
  ::google::protobuf::uint32 uiexchobjid_;
  mutable int _cached_size_;
  friend struct ::protobuf_ME_2eMESubcribeAPI_2eproto::TableStruct;
  friend void ::protobuf_ME_2eMESubcribeAPI_2eproto::InitDefaultsST_TRANS_ORDER_INFOImpl();
};
// -------------------------------------------------------------------

class ST_MART_QUOTATION : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:MESubcribeAPI.ST_MART_QUOTATION) */ {
 public:
  ST_MART_QUOTATION();
  virtual ~ST_MART_QUOTATION();

  ST_MART_QUOTATION(const ST_MART_QUOTATION& from);

  inline ST_MART_QUOTATION& operator=(const ST_MART_QUOTATION& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  ST_MART_QUOTATION(ST_MART_QUOTATION&& from) noexcept
    : ST_MART_QUOTATION() {
    *this = ::std::move(from);
  }

  inline ST_MART_QUOTATION& operator=(ST_MART_QUOTATION&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const ST_MART_QUOTATION& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ST_MART_QUOTATION* internal_default_instance() {
    return reinterpret_cast<const ST_MART_QUOTATION*>(
               &_ST_MART_QUOTATION_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(ST_MART_QUOTATION* other);
  friend void swap(ST_MART_QUOTATION& a, ST_MART_QUOTATION& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline ST_MART_QUOTATION* New() const PROTOBUF_FINAL { return New(NULL); }

  ST_MART_QUOTATION* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const ST_MART_QUOTATION& from);
  void MergeFrom(const ST_MART_QUOTATION& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(ST_MART_QUOTATION* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // uint32 uiUserID = 1;
  void clear_uiuserid();
  static const int kUiUserIDFieldNumber = 1;
  ::google::protobuf::uint32 uiuserid() const;
  void set_uiuserid(::google::protobuf::uint32 value);

  // uint32 uiExchObjID = 2;
  void clear_uiexchobjid();
  static const int kUiExchObjIDFieldNumber = 2;
  ::google::protobuf::uint32 uiexchobjid() const;
  void set_uiexchobjid(::google::protobuf::uint32 value);

  // int64 lCurDealProce = 3;
  void clear_lcurdealproce();
  static const int kLCurDealProceFieldNumber = 3;
  ::google::protobuf::int64 lcurdealproce() const;
  void set_lcurdealproce(::google::protobuf::int64 value);

  // int64 lTotalDealProce = 4;
  void clear_ltotaldealproce();
  static const int kLTotalDealProceFieldNumber = 4;
  ::google::protobuf::int64 ltotaldealproce() const;
  void set_ltotaldealproce(::google::protobuf::int64 value);

  // int64 lBeginProce = 5;
  void clear_lbeginproce();
  static const int kLBeginProceFieldNumber = 5;
  ::google::protobuf::int64 lbeginproce() const;
  void set_lbeginproce(::google::protobuf::int64 value);

  // int64 lHighestProce = 6;
  void clear_lhighestproce();
  static const int kLHighestProceFieldNumber = 6;
  ::google::protobuf::int64 lhighestproce() const;
  void set_lhighestproce(::google::protobuf::int64 value);

  // int64 lMinimumProce = 7;
  void clear_lminimumproce();
  static const int kLMinimumProceFieldNumber = 7;
  ::google::protobuf::int64 lminimumproce() const;
  void set_lminimumproce(::google::protobuf::int64 value);

  // @@protoc_insertion_point(class_scope:MESubcribeAPI.ST_MART_QUOTATION)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 uiuserid_;
  ::google::protobuf::uint32 uiexchobjid_;
  ::google::protobuf::int64 lcurdealproce_;
  ::google::protobuf::int64 ltotaldealproce_;
  ::google::protobuf::int64 lbeginproce_;
  ::google::protobuf::int64 lhighestproce_;
  ::google::protobuf::int64 lminimumproce_;
  mutable int _cached_size_;
  friend struct ::protobuf_ME_2eMESubcribeAPI_2eproto::TableStruct;
  friend void ::protobuf_ME_2eMESubcribeAPI_2eproto::InitDefaultsST_MART_QUOTATIONImpl();
};
// -------------------------------------------------------------------

class ST_REP_TRANS_ORDER_REQUEST : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:MESubcribeAPI.ST_REP_TRANS_ORDER_REQUEST) */ {
 public:
  ST_REP_TRANS_ORDER_REQUEST();
  virtual ~ST_REP_TRANS_ORDER_REQUEST();

  ST_REP_TRANS_ORDER_REQUEST(const ST_REP_TRANS_ORDER_REQUEST& from);

  inline ST_REP_TRANS_ORDER_REQUEST& operator=(const ST_REP_TRANS_ORDER_REQUEST& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  ST_REP_TRANS_ORDER_REQUEST(ST_REP_TRANS_ORDER_REQUEST&& from) noexcept
    : ST_REP_TRANS_ORDER_REQUEST() {
    *this = ::std::move(from);
  }

  inline ST_REP_TRANS_ORDER_REQUEST& operator=(ST_REP_TRANS_ORDER_REQUEST&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const ST_REP_TRANS_ORDER_REQUEST& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ST_REP_TRANS_ORDER_REQUEST* internal_default_instance() {
    return reinterpret_cast<const ST_REP_TRANS_ORDER_REQUEST*>(
               &_ST_REP_TRANS_ORDER_REQUEST_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    2;

  void Swap(ST_REP_TRANS_ORDER_REQUEST* other);
  friend void swap(ST_REP_TRANS_ORDER_REQUEST& a, ST_REP_TRANS_ORDER_REQUEST& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline ST_REP_TRANS_ORDER_REQUEST* New() const PROTOBUF_FINAL { return New(NULL); }

  ST_REP_TRANS_ORDER_REQUEST* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const ST_REP_TRANS_ORDER_REQUEST& from);
  void MergeFrom(const ST_REP_TRANS_ORDER_REQUEST& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(ST_REP_TRANS_ORDER_REQUEST* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // uint64 ucExchID = 2;
  void clear_ucexchid();
  static const int kUcExchIDFieldNumber = 2;
  ::google::protobuf::uint64 ucexchid() const;
  void set_ucexchid(::google::protobuf::uint64 value);

  // uint32 uiUserID = 1;
  void clear_uiuserid();
  static const int kUiUserIDFieldNumber = 1;
  ::google::protobuf::uint32 uiuserid() const;
  void set_uiuserid(::google::protobuf::uint32 value);

  // uint32 uiExchObjID = 3;
  void clear_uiexchobjid();
  static const int kUiExchObjIDFieldNumber = 3;
  ::google::protobuf::uint32 uiexchobjid() const;
  void set_uiexchobjid(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:MESubcribeAPI.ST_REP_TRANS_ORDER_REQUEST)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint64 ucexchid_;
  ::google::protobuf::uint32 uiuserid_;
  ::google::protobuf::uint32 uiexchobjid_;
  mutable int _cached_size_;
  friend struct ::protobuf_ME_2eMESubcribeAPI_2eproto::TableStruct;
  friend void ::protobuf_ME_2eMESubcribeAPI_2eproto::InitDefaultsST_REP_TRANS_ORDER_REQUESTImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ST_TRANS_ORDER_INFO

// string strBidOrderID = 1;
inline void ST_TRANS_ORDER_INFO::clear_strbidorderid() {
  strbidorderid_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& ST_TRANS_ORDER_INFO::strbidorderid() const {
  // @@protoc_insertion_point(field_get:MESubcribeAPI.ST_TRANS_ORDER_INFO.strBidOrderID)
  return strbidorderid_.GetNoArena();
}
inline void ST_TRANS_ORDER_INFO::set_strbidorderid(const ::std::string& value) {
  
  strbidorderid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:MESubcribeAPI.ST_TRANS_ORDER_INFO.strBidOrderID)
}
#if LANG_CXX11
inline void ST_TRANS_ORDER_INFO::set_strbidorderid(::std::string&& value) {
  
  strbidorderid_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:MESubcribeAPI.ST_TRANS_ORDER_INFO.strBidOrderID)
}
#endif
inline void ST_TRANS_ORDER_INFO::set_strbidorderid(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  strbidorderid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:MESubcribeAPI.ST_TRANS_ORDER_INFO.strBidOrderID)
}
inline void ST_TRANS_ORDER_INFO::set_strbidorderid(const char* value, size_t size) {
  
  strbidorderid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:MESubcribeAPI.ST_TRANS_ORDER_INFO.strBidOrderID)
}
inline ::std::string* ST_TRANS_ORDER_INFO::mutable_strbidorderid() {
  
  // @@protoc_insertion_point(field_mutable:MESubcribeAPI.ST_TRANS_ORDER_INFO.strBidOrderID)
  return strbidorderid_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ST_TRANS_ORDER_INFO::release_strbidorderid() {
  // @@protoc_insertion_point(field_release:MESubcribeAPI.ST_TRANS_ORDER_INFO.strBidOrderID)
  
  return strbidorderid_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ST_TRANS_ORDER_INFO::set_allocated_strbidorderid(::std::string* strbidorderid) {
  if (strbidorderid != NULL) {
    
  } else {
    
  }
  strbidorderid_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), strbidorderid);
  // @@protoc_insertion_point(field_set_allocated:MESubcribeAPI.ST_TRANS_ORDER_INFO.strBidOrderID)
}

// string strAskOrderID = 2;
inline void ST_TRANS_ORDER_INFO::clear_straskorderid() {
  straskorderid_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& ST_TRANS_ORDER_INFO::straskorderid() const {
  // @@protoc_insertion_point(field_get:MESubcribeAPI.ST_TRANS_ORDER_INFO.strAskOrderID)
  return straskorderid_.GetNoArena();
}
inline void ST_TRANS_ORDER_INFO::set_straskorderid(const ::std::string& value) {
  
  straskorderid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:MESubcribeAPI.ST_TRANS_ORDER_INFO.strAskOrderID)
}
#if LANG_CXX11
inline void ST_TRANS_ORDER_INFO::set_straskorderid(::std::string&& value) {
  
  straskorderid_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:MESubcribeAPI.ST_TRANS_ORDER_INFO.strAskOrderID)
}
#endif
inline void ST_TRANS_ORDER_INFO::set_straskorderid(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  straskorderid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:MESubcribeAPI.ST_TRANS_ORDER_INFO.strAskOrderID)
}
inline void ST_TRANS_ORDER_INFO::set_straskorderid(const char* value, size_t size) {
  
  straskorderid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:MESubcribeAPI.ST_TRANS_ORDER_INFO.strAskOrderID)
}
inline ::std::string* ST_TRANS_ORDER_INFO::mutable_straskorderid() {
  
  // @@protoc_insertion_point(field_mutable:MESubcribeAPI.ST_TRANS_ORDER_INFO.strAskOrderID)
  return straskorderid_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ST_TRANS_ORDER_INFO::release_straskorderid() {
  // @@protoc_insertion_point(field_release:MESubcribeAPI.ST_TRANS_ORDER_INFO.strAskOrderID)
  
  return straskorderid_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ST_TRANS_ORDER_INFO::set_allocated_straskorderid(::std::string* straskorderid) {
  if (straskorderid != NULL) {
    
  } else {
    
  }
  straskorderid_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), straskorderid);
  // @@protoc_insertion_point(field_set_allocated:MESubcribeAPI.ST_TRANS_ORDER_INFO.strAskOrderID)
}

// uint32 uiBidUserID = 3;
inline void ST_TRANS_ORDER_INFO::clear_uibiduserid() {
  uibiduserid_ = 0u;
}
inline ::google::protobuf::uint32 ST_TRANS_ORDER_INFO::uibiduserid() const {
  // @@protoc_insertion_point(field_get:MESubcribeAPI.ST_TRANS_ORDER_INFO.uiBidUserID)
  return uibiduserid_;
}
inline void ST_TRANS_ORDER_INFO::set_uibiduserid(::google::protobuf::uint32 value) {
  
  uibiduserid_ = value;
  // @@protoc_insertion_point(field_set:MESubcribeAPI.ST_TRANS_ORDER_INFO.uiBidUserID)
}

// uint32 uiAskUserID = 4;
inline void ST_TRANS_ORDER_INFO::clear_uiaskuserid() {
  uiaskuserid_ = 0u;
}
inline ::google::protobuf::uint32 ST_TRANS_ORDER_INFO::uiaskuserid() const {
  // @@protoc_insertion_point(field_get:MESubcribeAPI.ST_TRANS_ORDER_INFO.uiAskUserID)
  return uiaskuserid_;
}
inline void ST_TRANS_ORDER_INFO::set_uiaskuserid(::google::protobuf::uint32 value) {
  
  uiaskuserid_ = value;
  // @@protoc_insertion_point(field_set:MESubcribeAPI.ST_TRANS_ORDER_INFO.uiAskUserID)
}

// int64 fPrice = 5;
inline void ST_TRANS_ORDER_INFO::clear_fprice() {
  fprice_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 ST_TRANS_ORDER_INFO::fprice() const {
  // @@protoc_insertion_point(field_get:MESubcribeAPI.ST_TRANS_ORDER_INFO.fPrice)
  return fprice_;
}
inline void ST_TRANS_ORDER_INFO::set_fprice(::google::protobuf::int64 value) {
  
  fprice_ = value;
  // @@protoc_insertion_point(field_set:MESubcribeAPI.ST_TRANS_ORDER_INFO.fPrice)
}

// int64 fNumber = 6;
inline void ST_TRANS_ORDER_INFO::clear_fnumber() {
  fnumber_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 ST_TRANS_ORDER_INFO::fnumber() const {
  // @@protoc_insertion_point(field_get:MESubcribeAPI.ST_TRANS_ORDER_INFO.fNumber)
  return fnumber_;
}
inline void ST_TRANS_ORDER_INFO::set_fnumber(::google::protobuf::int64 value) {
  
  fnumber_ = value;
  // @@protoc_insertion_point(field_set:MESubcribeAPI.ST_TRANS_ORDER_INFO.fNumber)
}

// uint32 ucExchType = 7;
inline void ST_TRANS_ORDER_INFO::clear_ucexchtype() {
  ucexchtype_ = 0u;
}
inline ::google::protobuf::uint32 ST_TRANS_ORDER_INFO::ucexchtype() const {
  // @@protoc_insertion_point(field_get:MESubcribeAPI.ST_TRANS_ORDER_INFO.ucExchType)
  return ucexchtype_;
}
inline void ST_TRANS_ORDER_INFO::set_ucexchtype(::google::protobuf::uint32 value) {
  
  ucexchtype_ = value;
  // @@protoc_insertion_point(field_set:MESubcribeAPI.ST_TRANS_ORDER_INFO.ucExchType)
}

// uint64 ucRecordID = 8;
inline void ST_TRANS_ORDER_INFO::clear_ucrecordid() {
  ucrecordid_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 ST_TRANS_ORDER_INFO::ucrecordid() const {
  // @@protoc_insertion_point(field_get:MESubcribeAPI.ST_TRANS_ORDER_INFO.ucRecordID)
  return ucrecordid_;
}
inline void ST_TRANS_ORDER_INFO::set_ucrecordid(::google::protobuf::uint64 value) {
  
  ucrecordid_ = value;
  // @@protoc_insertion_point(field_set:MESubcribeAPI.ST_TRANS_ORDER_INFO.ucRecordID)
}

// uint32 ucOrderStatus = 9;
inline void ST_TRANS_ORDER_INFO::clear_ucorderstatus() {
  ucorderstatus_ = 0u;
}
inline ::google::protobuf::uint32 ST_TRANS_ORDER_INFO::ucorderstatus() const {
  // @@protoc_insertion_point(field_get:MESubcribeAPI.ST_TRANS_ORDER_INFO.ucOrderStatus)
  return ucorderstatus_;
}
inline void ST_TRANS_ORDER_INFO::set_ucorderstatus(::google::protobuf::uint32 value) {
  
  ucorderstatus_ = value;
  // @@protoc_insertion_point(field_set:MESubcribeAPI.ST_TRANS_ORDER_INFO.ucOrderStatus)
}

// uint32 uiExchObjID = 10;
inline void ST_TRANS_ORDER_INFO::clear_uiexchobjid() {
  uiexchobjid_ = 0u;
}
inline ::google::protobuf::uint32 ST_TRANS_ORDER_INFO::uiexchobjid() const {
  // @@protoc_insertion_point(field_get:MESubcribeAPI.ST_TRANS_ORDER_INFO.uiExchObjID)
  return uiexchobjid_;
}
inline void ST_TRANS_ORDER_INFO::set_uiexchobjid(::google::protobuf::uint32 value) {
  
  uiexchobjid_ = value;
  // @@protoc_insertion_point(field_set:MESubcribeAPI.ST_TRANS_ORDER_INFO.uiExchObjID)
}

// uint64 meBidOrderID = 11;
inline void ST_TRANS_ORDER_INFO::clear_mebidorderid() {
  mebidorderid_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 ST_TRANS_ORDER_INFO::mebidorderid() const {
  // @@protoc_insertion_point(field_get:MESubcribeAPI.ST_TRANS_ORDER_INFO.meBidOrderID)
  return mebidorderid_;
}
inline void ST_TRANS_ORDER_INFO::set_mebidorderid(::google::protobuf::uint64 value) {
  
  mebidorderid_ = value;
  // @@protoc_insertion_point(field_set:MESubcribeAPI.ST_TRANS_ORDER_INFO.meBidOrderID)
}

// uint64 meAskOrderID = 12;
inline void ST_TRANS_ORDER_INFO::clear_measkorderid() {
  measkorderid_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 ST_TRANS_ORDER_INFO::measkorderid() const {
  // @@protoc_insertion_point(field_get:MESubcribeAPI.ST_TRANS_ORDER_INFO.meAskOrderID)
  return measkorderid_;
}
inline void ST_TRANS_ORDER_INFO::set_measkorderid(::google::protobuf::uint64 value) {
  
  measkorderid_ = value;
  // @@protoc_insertion_point(field_set:MESubcribeAPI.ST_TRANS_ORDER_INFO.meAskOrderID)
}

// -------------------------------------------------------------------

// ST_MART_QUOTATION

// uint32 uiUserID = 1;
inline void ST_MART_QUOTATION::clear_uiuserid() {
  uiuserid_ = 0u;
}
inline ::google::protobuf::uint32 ST_MART_QUOTATION::uiuserid() const {
  // @@protoc_insertion_point(field_get:MESubcribeAPI.ST_MART_QUOTATION.uiUserID)
  return uiuserid_;
}
inline void ST_MART_QUOTATION::set_uiuserid(::google::protobuf::uint32 value) {
  
  uiuserid_ = value;
  // @@protoc_insertion_point(field_set:MESubcribeAPI.ST_MART_QUOTATION.uiUserID)
}

// uint32 uiExchObjID = 2;
inline void ST_MART_QUOTATION::clear_uiexchobjid() {
  uiexchobjid_ = 0u;
}
inline ::google::protobuf::uint32 ST_MART_QUOTATION::uiexchobjid() const {
  // @@protoc_insertion_point(field_get:MESubcribeAPI.ST_MART_QUOTATION.uiExchObjID)
  return uiexchobjid_;
}
inline void ST_MART_QUOTATION::set_uiexchobjid(::google::protobuf::uint32 value) {
  
  uiexchobjid_ = value;
  // @@protoc_insertion_point(field_set:MESubcribeAPI.ST_MART_QUOTATION.uiExchObjID)
}

// int64 lCurDealProce = 3;
inline void ST_MART_QUOTATION::clear_lcurdealproce() {
  lcurdealproce_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 ST_MART_QUOTATION::lcurdealproce() const {
  // @@protoc_insertion_point(field_get:MESubcribeAPI.ST_MART_QUOTATION.lCurDealProce)
  return lcurdealproce_;
}
inline void ST_MART_QUOTATION::set_lcurdealproce(::google::protobuf::int64 value) {
  
  lcurdealproce_ = value;
  // @@protoc_insertion_point(field_set:MESubcribeAPI.ST_MART_QUOTATION.lCurDealProce)
}

// int64 lTotalDealProce = 4;
inline void ST_MART_QUOTATION::clear_ltotaldealproce() {
  ltotaldealproce_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 ST_MART_QUOTATION::ltotaldealproce() const {
  // @@protoc_insertion_point(field_get:MESubcribeAPI.ST_MART_QUOTATION.lTotalDealProce)
  return ltotaldealproce_;
}
inline void ST_MART_QUOTATION::set_ltotaldealproce(::google::protobuf::int64 value) {
  
  ltotaldealproce_ = value;
  // @@protoc_insertion_point(field_set:MESubcribeAPI.ST_MART_QUOTATION.lTotalDealProce)
}

// int64 lBeginProce = 5;
inline void ST_MART_QUOTATION::clear_lbeginproce() {
  lbeginproce_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 ST_MART_QUOTATION::lbeginproce() const {
  // @@protoc_insertion_point(field_get:MESubcribeAPI.ST_MART_QUOTATION.lBeginProce)
  return lbeginproce_;
}
inline void ST_MART_QUOTATION::set_lbeginproce(::google::protobuf::int64 value) {
  
  lbeginproce_ = value;
  // @@protoc_insertion_point(field_set:MESubcribeAPI.ST_MART_QUOTATION.lBeginProce)
}

// int64 lHighestProce = 6;
inline void ST_MART_QUOTATION::clear_lhighestproce() {
  lhighestproce_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 ST_MART_QUOTATION::lhighestproce() const {
  // @@protoc_insertion_point(field_get:MESubcribeAPI.ST_MART_QUOTATION.lHighestProce)
  return lhighestproce_;
}
inline void ST_MART_QUOTATION::set_lhighestproce(::google::protobuf::int64 value) {
  
  lhighestproce_ = value;
  // @@protoc_insertion_point(field_set:MESubcribeAPI.ST_MART_QUOTATION.lHighestProce)
}

// int64 lMinimumProce = 7;
inline void ST_MART_QUOTATION::clear_lminimumproce() {
  lminimumproce_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 ST_MART_QUOTATION::lminimumproce() const {
  // @@protoc_insertion_point(field_get:MESubcribeAPI.ST_MART_QUOTATION.lMinimumProce)
  return lminimumproce_;
}
inline void ST_MART_QUOTATION::set_lminimumproce(::google::protobuf::int64 value) {
  
  lminimumproce_ = value;
  // @@protoc_insertion_point(field_set:MESubcribeAPI.ST_MART_QUOTATION.lMinimumProce)
}

// -------------------------------------------------------------------

// ST_REP_TRANS_ORDER_REQUEST

// uint32 uiUserID = 1;
inline void ST_REP_TRANS_ORDER_REQUEST::clear_uiuserid() {
  uiuserid_ = 0u;
}
inline ::google::protobuf::uint32 ST_REP_TRANS_ORDER_REQUEST::uiuserid() const {
  // @@protoc_insertion_point(field_get:MESubcribeAPI.ST_REP_TRANS_ORDER_REQUEST.uiUserID)
  return uiuserid_;
}
inline void ST_REP_TRANS_ORDER_REQUEST::set_uiuserid(::google::protobuf::uint32 value) {
  
  uiuserid_ = value;
  // @@protoc_insertion_point(field_set:MESubcribeAPI.ST_REP_TRANS_ORDER_REQUEST.uiUserID)
}

// uint64 ucExchID = 2;
inline void ST_REP_TRANS_ORDER_REQUEST::clear_ucexchid() {
  ucexchid_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 ST_REP_TRANS_ORDER_REQUEST::ucexchid() const {
  // @@protoc_insertion_point(field_get:MESubcribeAPI.ST_REP_TRANS_ORDER_REQUEST.ucExchID)
  return ucexchid_;
}
inline void ST_REP_TRANS_ORDER_REQUEST::set_ucexchid(::google::protobuf::uint64 value) {
  
  ucexchid_ = value;
  // @@protoc_insertion_point(field_set:MESubcribeAPI.ST_REP_TRANS_ORDER_REQUEST.ucExchID)
}

// uint32 uiExchObjID = 3;
inline void ST_REP_TRANS_ORDER_REQUEST::clear_uiexchobjid() {
  uiexchobjid_ = 0u;
}
inline ::google::protobuf::uint32 ST_REP_TRANS_ORDER_REQUEST::uiexchobjid() const {
  // @@protoc_insertion_point(field_get:MESubcribeAPI.ST_REP_TRANS_ORDER_REQUEST.uiExchObjID)
  return uiexchobjid_;
}
inline void ST_REP_TRANS_ORDER_REQUEST::set_uiexchobjid(::google::protobuf::uint32 value) {
  
  uiexchobjid_ = value;
  // @@protoc_insertion_point(field_set:MESubcribeAPI.ST_REP_TRANS_ORDER_REQUEST.uiExchObjID)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace MESubcribeAPI

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ME_2eMESubcribeAPI_2eproto__INCLUDED
