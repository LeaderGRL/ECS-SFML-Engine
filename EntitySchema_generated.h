// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_ENTITYSCHEMA_LEADERENGINE_H_
#define FLATBUFFERS_GENERATED_ENTITYSCHEMA_LEADERENGINE_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 23 &&
              FLATBUFFERS_VERSION_MINOR == 5 &&
              FLATBUFFERS_VERSION_REVISION == 26,
             "Non-compatible flatbuffers version included");

namespace LeaderEngine {

struct Vec2;
struct Vec2Builder;

struct Transform;
struct TransformBuilder;

struct Sprite2DComponent;
struct Sprite2DComponentBuilder;

struct Animation2DComponent;
struct Animation2DComponentBuilder;

struct EntitySchema;
struct EntitySchemaBuilder;

enum Component : uint8_t {
  Component_NONE = 0,
  Component_Sprite2DComponent = 1,
  Component_Animation2DComponent = 2,
  Component_MIN = Component_NONE,
  Component_MAX = Component_Animation2DComponent
};

inline const Component (&EnumValuesComponent())[3] {
  static const Component values[] = {
    Component_NONE,
    Component_Sprite2DComponent,
    Component_Animation2DComponent
  };
  return values;
}

inline const char * const *EnumNamesComponent() {
  static const char * const names[4] = {
    "NONE",
    "Sprite2DComponent",
    "Animation2DComponent",
    nullptr
  };
  return names;
}

inline const char *EnumNameComponent(Component e) {
  if (::flatbuffers::IsOutRange(e, Component_NONE, Component_Animation2DComponent)) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesComponent()[index];
}

template<typename T> struct ComponentTraits {
  static const Component enum_value = Component_NONE;
};

template<> struct ComponentTraits<LeaderEngine::Sprite2DComponent> {
  static const Component enum_value = Component_Sprite2DComponent;
};

template<> struct ComponentTraits<LeaderEngine::Animation2DComponent> {
  static const Component enum_value = Component_Animation2DComponent;
};

bool VerifyComponent(::flatbuffers::Verifier &verifier, const void *obj, Component type);
bool VerifyComponentVector(::flatbuffers::Verifier &verifier, const ::flatbuffers::Vector<::flatbuffers::Offset<void>> *values, const ::flatbuffers::Vector<uint8_t> *types);

struct Vec2 FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef Vec2Builder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_X = 4,
    VT_Y = 6
  };
  float x() const {
    return GetField<float>(VT_X, 0.0f);
  }
  float y() const {
    return GetField<float>(VT_Y, 0.0f);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_X, 4) &&
           VerifyField<float>(verifier, VT_Y, 4) &&
           verifier.EndTable();
  }
};

struct Vec2Builder {
  typedef Vec2 Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_x(float x) {
    fbb_.AddElement<float>(Vec2::VT_X, x, 0.0f);
  }
  void add_y(float y) {
    fbb_.AddElement<float>(Vec2::VT_Y, y, 0.0f);
  }
  explicit Vec2Builder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Vec2> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Vec2>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<Vec2> CreateVec2(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    float x = 0.0f,
    float y = 0.0f) {
  Vec2Builder builder_(_fbb);
  builder_.add_y(y);
  builder_.add_x(x);
  return builder_.Finish();
}

struct Transform FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef TransformBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_POSITION = 4,
    VT_ROTATION = 6,
    VT_SCALE = 8
  };
  const LeaderEngine::Vec2 *position() const {
    return GetPointer<const LeaderEngine::Vec2 *>(VT_POSITION);
  }
  float rotation() const {
    return GetField<float>(VT_ROTATION, 0.0f);
  }
  const LeaderEngine::Vec2 *scale() const {
    return GetPointer<const LeaderEngine::Vec2 *>(VT_SCALE);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_POSITION) &&
           verifier.VerifyTable(position()) &&
           VerifyField<float>(verifier, VT_ROTATION, 4) &&
           VerifyOffset(verifier, VT_SCALE) &&
           verifier.VerifyTable(scale()) &&
           verifier.EndTable();
  }
};

struct TransformBuilder {
  typedef Transform Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_position(::flatbuffers::Offset<LeaderEngine::Vec2> position) {
    fbb_.AddOffset(Transform::VT_POSITION, position);
  }
  void add_rotation(float rotation) {
    fbb_.AddElement<float>(Transform::VT_ROTATION, rotation, 0.0f);
  }
  void add_scale(::flatbuffers::Offset<LeaderEngine::Vec2> scale) {
    fbb_.AddOffset(Transform::VT_SCALE, scale);
  }
  explicit TransformBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Transform> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Transform>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<Transform> CreateTransform(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<LeaderEngine::Vec2> position = 0,
    float rotation = 0.0f,
    ::flatbuffers::Offset<LeaderEngine::Vec2> scale = 0) {
  TransformBuilder builder_(_fbb);
  builder_.add_scale(scale);
  builder_.add_rotation(rotation);
  builder_.add_position(position);
  return builder_.Finish();
}

struct Sprite2DComponent FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef Sprite2DComponentBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TEXTURE_NAME = 4
  };
  const ::flatbuffers::String *texture_name() const {
    return GetPointer<const ::flatbuffers::String *>(VT_TEXTURE_NAME);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_TEXTURE_NAME) &&
           verifier.VerifyString(texture_name()) &&
           verifier.EndTable();
  }
};

struct Sprite2DComponentBuilder {
  typedef Sprite2DComponent Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_texture_name(::flatbuffers::Offset<::flatbuffers::String> texture_name) {
    fbb_.AddOffset(Sprite2DComponent::VT_TEXTURE_NAME, texture_name);
  }
  explicit Sprite2DComponentBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Sprite2DComponent> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Sprite2DComponent>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<Sprite2DComponent> CreateSprite2DComponent(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<::flatbuffers::String> texture_name = 0) {
  Sprite2DComponentBuilder builder_(_fbb);
  builder_.add_texture_name(texture_name);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<Sprite2DComponent> CreateSprite2DComponentDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const char *texture_name = nullptr) {
  auto texture_name__ = texture_name ? _fbb.CreateString(texture_name) : 0;
  return LeaderEngine::CreateSprite2DComponent(
      _fbb,
      texture_name__);
}

struct Animation2DComponent FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef Animation2DComponentBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_ANIMATION_NAME = 4,
    VT_SHOULD_LOOP = 6,
    VT_IS_ANIMATING = 8
  };
  const ::flatbuffers::String *animation_name() const {
    return GetPointer<const ::flatbuffers::String *>(VT_ANIMATION_NAME);
  }
  bool should_loop() const {
    return GetField<uint8_t>(VT_SHOULD_LOOP, 0) != 0;
  }
  bool is_animating() const {
    return GetField<uint8_t>(VT_IS_ANIMATING, 0) != 0;
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_ANIMATION_NAME) &&
           verifier.VerifyString(animation_name()) &&
           VerifyField<uint8_t>(verifier, VT_SHOULD_LOOP, 1) &&
           VerifyField<uint8_t>(verifier, VT_IS_ANIMATING, 1) &&
           verifier.EndTable();
  }
};

struct Animation2DComponentBuilder {
  typedef Animation2DComponent Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_animation_name(::flatbuffers::Offset<::flatbuffers::String> animation_name) {
    fbb_.AddOffset(Animation2DComponent::VT_ANIMATION_NAME, animation_name);
  }
  void add_should_loop(bool should_loop) {
    fbb_.AddElement<uint8_t>(Animation2DComponent::VT_SHOULD_LOOP, static_cast<uint8_t>(should_loop), 0);
  }
  void add_is_animating(bool is_animating) {
    fbb_.AddElement<uint8_t>(Animation2DComponent::VT_IS_ANIMATING, static_cast<uint8_t>(is_animating), 0);
  }
  explicit Animation2DComponentBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<Animation2DComponent> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<Animation2DComponent>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<Animation2DComponent> CreateAnimation2DComponent(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    ::flatbuffers::Offset<::flatbuffers::String> animation_name = 0,
    bool should_loop = false,
    bool is_animating = false) {
  Animation2DComponentBuilder builder_(_fbb);
  builder_.add_animation_name(animation_name);
  builder_.add_is_animating(is_animating);
  builder_.add_should_loop(should_loop);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<Animation2DComponent> CreateAnimation2DComponentDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    const char *animation_name = nullptr,
    bool should_loop = false,
    bool is_animating = false) {
  auto animation_name__ = animation_name ? _fbb.CreateString(animation_name) : 0;
  return LeaderEngine::CreateAnimation2DComponent(
      _fbb,
      animation_name__,
      should_loop,
      is_animating);
}

struct EntitySchema FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef EntitySchemaBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_ID = 4,
    VT_TRANSFORM = 6,
    VT_COMPONENTS_TYPE = 8,
    VT_COMPONENTS = 10
  };
  int32_t id() const {
    return GetField<int32_t>(VT_ID, 0);
  }
  const LeaderEngine::Transform *transform() const {
    return GetPointer<const LeaderEngine::Transform *>(VT_TRANSFORM);
  }
  const ::flatbuffers::Vector<uint8_t> *components_type() const {
    return GetPointer<const ::flatbuffers::Vector<uint8_t> *>(VT_COMPONENTS_TYPE);
  }
  const ::flatbuffers::Vector<::flatbuffers::Offset<void>> *components() const {
    return GetPointer<const ::flatbuffers::Vector<::flatbuffers::Offset<void>> *>(VT_COMPONENTS);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_ID, 4) &&
           VerifyOffset(verifier, VT_TRANSFORM) &&
           verifier.VerifyTable(transform()) &&
           VerifyOffset(verifier, VT_COMPONENTS_TYPE) &&
           verifier.VerifyVector(components_type()) &&
           VerifyOffset(verifier, VT_COMPONENTS) &&
           verifier.VerifyVector(components()) &&
           VerifyComponentVector(verifier, components(), components_type()) &&
           verifier.EndTable();
  }
};

struct EntitySchemaBuilder {
  typedef EntitySchema Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_id(int32_t id) {
    fbb_.AddElement<int32_t>(EntitySchema::VT_ID, id, 0);
  }
  void add_transform(::flatbuffers::Offset<LeaderEngine::Transform> transform) {
    fbb_.AddOffset(EntitySchema::VT_TRANSFORM, transform);
  }
  void add_components_type(::flatbuffers::Offset<::flatbuffers::Vector<uint8_t>> components_type) {
    fbb_.AddOffset(EntitySchema::VT_COMPONENTS_TYPE, components_type);
  }
  void add_components(::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<void>>> components) {
    fbb_.AddOffset(EntitySchema::VT_COMPONENTS, components);
  }
  explicit EntitySchemaBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<EntitySchema> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<EntitySchema>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<EntitySchema> CreateEntitySchema(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    int32_t id = 0,
    ::flatbuffers::Offset<LeaderEngine::Transform> transform = 0,
    ::flatbuffers::Offset<::flatbuffers::Vector<uint8_t>> components_type = 0,
    ::flatbuffers::Offset<::flatbuffers::Vector<::flatbuffers::Offset<void>>> components = 0) {
  EntitySchemaBuilder builder_(_fbb);
  builder_.add_components(components);
  builder_.add_components_type(components_type);
  builder_.add_transform(transform);
  builder_.add_id(id);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<EntitySchema> CreateEntitySchemaDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    int32_t id = 0,
    ::flatbuffers::Offset<LeaderEngine::Transform> transform = 0,
    const std::vector<uint8_t> *components_type = nullptr,
    const std::vector<::flatbuffers::Offset<void>> *components = nullptr) {
  auto components_type__ = components_type ? _fbb.CreateVector<uint8_t>(*components_type) : 0;
  auto components__ = components ? _fbb.CreateVector<::flatbuffers::Offset<void>>(*components) : 0;
  return LeaderEngine::CreateEntitySchema(
      _fbb,
      id,
      transform,
      components_type__,
      components__);
}

inline bool VerifyComponent(::flatbuffers::Verifier &verifier, const void *obj, Component type) {
  switch (type) {
    case Component_NONE: {
      return true;
    }
    case Component_Sprite2DComponent: {
      auto ptr = reinterpret_cast<const LeaderEngine::Sprite2DComponent *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case Component_Animation2DComponent: {
      auto ptr = reinterpret_cast<const LeaderEngine::Animation2DComponent *>(obj);
      return verifier.VerifyTable(ptr);
    }
    default: return true;
  }
}

inline bool VerifyComponentVector(::flatbuffers::Verifier &verifier, const ::flatbuffers::Vector<::flatbuffers::Offset<void>> *values, const ::flatbuffers::Vector<uint8_t> *types) {
  if (!values || !types) return !values && !types;
  if (values->size() != types->size()) return false;
  for (::flatbuffers::uoffset_t i = 0; i < values->size(); ++i) {
    if (!VerifyComponent(
        verifier,  values->Get(i), types->GetEnum<Component>(i))) {
      return false;
    }
  }
  return true;
}

inline const LeaderEngine::EntitySchema *GetEntitySchema(const void *buf) {
  return ::flatbuffers::GetRoot<LeaderEngine::EntitySchema>(buf);
}

inline const LeaderEngine::EntitySchema *GetSizePrefixedEntitySchema(const void *buf) {
  return ::flatbuffers::GetSizePrefixedRoot<LeaderEngine::EntitySchema>(buf);
}

inline bool VerifyEntitySchemaBuffer(
    ::flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<LeaderEngine::EntitySchema>(nullptr);
}

inline bool VerifySizePrefixedEntitySchemaBuffer(
    ::flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<LeaderEngine::EntitySchema>(nullptr);
}

inline void FinishEntitySchemaBuffer(
    ::flatbuffers::FlatBufferBuilder &fbb,
    ::flatbuffers::Offset<LeaderEngine::EntitySchema> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedEntitySchemaBuffer(
    ::flatbuffers::FlatBufferBuilder &fbb,
    ::flatbuffers::Offset<LeaderEngine::EntitySchema> root) {
  fbb.FinishSizePrefixed(root);
}

}  // namespace LeaderEngine

#endif  // FLATBUFFERS_GENERATED_ENTITYSCHEMA_LEADERENGINE_H_
