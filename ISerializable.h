#ifndef LEADERENGINE_ISERIALIZABLE_H
#define LEADERENGINE_ISERIALIZABLE_H

#include "flatbuffers/flatbuffers.h"

namespace LeaderEngine
{
	class ISerializable
	{
		public:
		    virtual ~ISerializable() = default; // virtual destructor to ensure proper cleanup of derived classes
			virtual flatbuffers::Offset<void> Serialize(flatbuffers::FlatBufferBuilder& builder) const = 0; // pure virtual function to be implemented by derived classes to serialize their data to a flatbuffer builder object 
			virtual std::shared_ptr<ISerializable> Deserialize(const void* buffer) = 0; // void* buffer to be casted to the appropriate type by the derived class to deserialize the data

			void SetDirty(bool dirty) { _dirty = dirty; }
			bool IsDirty() const { return _dirty; }

		private:
			bool _dirty = false;
	};
}

#endif // LEADERENGINE_ISERIALIZABLE_H
