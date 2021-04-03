#include "ecs_stuff.h"

void random_teleport_system(Query<const RandomTeleport, TransformComponent> &p_query) {
	for (auto [tag, transf] : p_query) {
		transf->transform.origin = Vector3(
				Math::random(-10.0, 10.0),
				Math::random(-10.0, 10.0),
				Math::random(-10.0, 10.0));
	}
}

void debris_system(const FrameTime *p_frame_time, Query<Debris, TransformComponent> &p_query) {
	for (auto [debris, transf] : p_query) {
		const Vector3 distance_to_center = transf->transform.origin * -1.0;
		debris->velocity += distance_to_center * p_frame_time->get_delta();
		transf->transform.origin += debris->velocity * p_frame_time->get_delta();
	}
}
