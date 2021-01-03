
#include "./register_types.h"

#include "../godex/ecs.h"
#include "ecs_stuff.h"
#include "nodes.h"

void register_test_nodes_and_systems_types() {
	// ~~ Nodes
	ClassDB::register_class<RandomTransformNode>();
	ClassDB::register_class<DebrisNode>();

	// ~~ ECS
	ECS::register_component<RandomTeleport>();
	ECS::register_component<Debris>();

	ECS::register_system(random_teleport_system, "RandomTeleport", "Random teleport system.");
	ECS::register_system(debris_system, "DebrisSystem", "Debris motion system.");
}

void unregister_test_nodes_and_systems_types() {
}
