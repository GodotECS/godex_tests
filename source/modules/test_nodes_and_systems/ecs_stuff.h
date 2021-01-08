
#pragma once

#include "../godex/components/component.h"
#include "../godex/godot/components/transform_component.h"
#include "../godex/godot/databags/godot_engine_databags.h"
#include "../godex/systems/system.h"
#include "core/config/engine.h"

class RandomTeleport : public godex::Component {
	COMPONENT(RandomTeleport, DenseVector)
};

class Debris : public godex::Component {
	COMPONENT(Debris, DenseVector)

	static void _bind_properties() {
		ECS_BIND_PROPERTY(Debris, PropertyInfo(Variant::VECTOR3, "velocity"), velocity);
	}

public:
	Vector3 velocity;
};

void random_teleport_system(Query<const RandomTeleport, TransformComponent> p_query);
void debris_system(const FrameTime *p_frame_time, Query<Debris, TransformComponent> p_query);
