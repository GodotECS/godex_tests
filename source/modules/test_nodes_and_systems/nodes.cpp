
#include "nodes.h"

void RandomTransformNode::_notification(int p_what) {
	if (p_what == NOTIFICATION_PROCESS) {
		set_transform(Transform(Basis(), Vector3(
												 Math::random(-10.0, 10.0),
												 Math::random(-10.0, 10.0),
												 Math::random(-10.0, 10.0))));
	} else if (p_what == NOTIFICATION_READY) {
		set_process(true);
	}
}

void DebrisNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_velocity"), &DebrisNode::set_velocity);
	ClassDB::bind_method(D_METHOD("get_velocity"), &DebrisNode::get_velocity);

	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "velocity"), "set_velocity", "get_velocity");
}

void DebrisNode::_notification(int p_what) {
	if (p_what == NOTIFICATION_PROCESS) {
		const Vector3 distance_to_center = get_transform().origin * -1.0;
		velocity += distance_to_center * get_process_delta_time();
		set_transform(Transform(Basis(), get_transform().origin += velocity * get_process_delta_time()));
	} else if (p_what == NOTIFICATION_READY) {
		set_process(true);
	}
}

void DebrisNode::set_velocity(const Vector3 &p_vel) {
	velocity = p_vel;
}

Vector3 DebrisNode::get_velocity() const {
	return velocity;
}
