/* Author: AndreaCatania */

#ifndef KINEMATIC_OBJECT_3D_H
#define KINEMATIC_OBJECT_3D_H

#include "scene/3d/node_3d.h"

class RandomTransformNode : public Node3D {
	GDCLASS(RandomTransformNode, Node3D)

public:
	void _notification(int p_what);
};

class DebrisNode : public Node3D {
	GDCLASS(DebrisNode, Node3D)

	Vector3 velocity;

	static void _bind_methods();

public:
	void _notification(int p_what);

	void set_velocity(const Vector3 &p_vel);
	Vector3 get_velocity() const;
};

#endif
