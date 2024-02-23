// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_SPRITE2DCOMPONENTSCHEMA_LEADERENGINE_H_
#define FLATBUFFERS_GENERATED_SPRITE2DCOMPONENTSCHEMA_LEADERENGINE_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 23 &&
              FLATBUFFERS_VERSION_MINOR == 5 &&
              FLATBUFFERS_VERSION_REVISION == 26,
             "Non-compatible flatbuffers version included");

namespace LeaderEngine {

struct Sprite2DComponentSchema;
struct Sprite2DComponentSchemaBuilder;

struct Sprite2DComponentSchema FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef Sprite2DComponentSchemaBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TEXTURE_NAME = 4,
    VT_ANIMATION_NAME = 6,
    VT_IS_ANIMATING = 8,
    VT_SHOULD_LOOP = 10
  };
  const ::flatbuffers::String *texture_name() const {
    return GetPointer<const ::flatbuffers::String *>(VT_TEXTURE_NAME);
  }
  const ::flatbuffers::String *animation_name() const {
    return GetPointer<const ::flatbuffers::String *>(VT_ANIMATION_NAME);
  }
  bool is_animating() const {
    return GetField<uint8_t>(VT_IS_ANIMATING, 0) != 0;
  }
  bool should_loop() const {
    return GetField<uint8_t>(VT_SHOULD_LOOP, 0) != 0;
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_TEXTURE_NAME) &&
           verifier.VerifyString(texture_name()) &&
           VerifyOffset(verifier, VT_ANIMATION_NAME) &&
           verifier.VerifyString(animation_name()) &&
           VerifyField<uint8_t>(verifier, VT_IS_ANIMATING, 1) &&
           VerifyField<uint8_t>(verifier, VT_SHOULD_LOOP, 1) &&
           verifier.EndTable();
  }
};

struct Sprite2DComponentSchemaBuilder {
  typedef Sprite2DComponentSchema Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_texture_name(::flatbuffers::Offset<::flatbuffers::String> texture_name) {
    fbb_.AddOffset(Sprite2DComponentSchema::VT_TEXTURE_NAME, texture_name);
  }
  void add_animation_name(::flatbuffers::Offset<::flatbuffers::String> animation_name) {
    fbb_.AddOffset(Sprite2DComponentSchema::VT_ANIMATION_NAME, animation_name);
  }
  void add_is_animating(bool is_animating) {
    fbb_.AddElement<uint8_t>(Sprite2DComponentSchema::VT_IS_ANIMATING, static_cast<uint8_t>(is_animating), 0);
  }
  void add_should_loop(bool should_loop) {
    fbb_.AddElement<uint8_t>(Sprite2DComponentSchema::VT_SHOULD_LOOP, static_cast<uint8_t>(should_loop), 0);
  }
  explicit Sprite2DComponentSchemaBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Sprite2DComponentSchema> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Sprite2DComponentSchema>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<Sprite2DComponentSchema> CreateSprite2DComponentSchema(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<::flatbuffers::String> texture_name = 0,
    ::flatbuffers::Offset<::flatbuffers::String> animation_name = 0,
    bool is_animating = false,
    bool should_loop = false) {
  Sprite2DComponentSchemaBuilder builder_(_fbb);
  builder_.add_animation_name(animation_name);
  builder_.add_texture_name(texture_name);
  builder_.add_should_loop(should_loop);
  builder_.add_is_animating(is_animating);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<Sprite2DComponentSchema> CreateSprite2DComponentSchemaDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const char *texture_name = nullptr,
    const char *animation_name = nullptr,
    bool is_animating = false,
    bool should_loop = false) {
  auto texture_name__ = texture_name ? _fbb.CreateString(texture_name) : 0;
  auto animation_name__ = animation_name ? _fbb.CreateString(animation_name) : 0;
  return LeaderEngine::CreateSprite2DComponentSchema(
      _fbb,
      texture_name__,
      animation_name__,
      is_animating,
      should_loop);
}

inline const LeaderEngine::Sprite2DComponentSchema *GetSprite2DComponentSchema(const void *buf) {
  return ::flatbuffers::GetRoot<LeaderEngine::Sprite2DComponentSchema>(buf);
}

inline const LeaderEngine::Sprite2DComponentSchema *GetSizePrefixedSprite2DComponentSchema(const void *buf) {
  return ::flatbuffers::GetSizePrefixedRoot<LeaderEngine::Sprite2DComponentSchema>(buf);
}

inline bool VerifySprite2DComponentSchemaBuffer(
    ::flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<LeaderEngine::Sprite2DComponentSchema>(nullptr);
}

inline bool VerifySizePrefixedSprite2DComponentSchemaBuffer(
    ::flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<LeaderEngine::Sprite2DComponentSchema>(nullptr);
}

inline void FinishSprite2DComponentSchemaBuffer(
    ::flatbuffers::FlatBufferBuilder &fbb,
    ::flatbuffers::Offset<LeaderEngine::Sprite2DComponentSchema> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedSprite2DComponentSchemaBuffer(
    ::flatbuffers::FlatBufferBuilder &fbb,
    ::flatbuffers::Offset<LeaderEngine::Sprite2DComponentSchema> root) {
  fbb.FinishSizePrefixed(root);
}

}  // namespace LeaderEngine

#endif  // FLATBUFFERS_GENERATED_SPRITE2DCOMPONENTSCHEMA_LEADERENGINE_H_