#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(2.0f, 0.75f, 3.0f);
	car.chassis_offset.Set(0.0f, 0.5f, 0.0f);
	car.bridge_size.Set(0.8f, 0.75f, 2.0f);
	car.bridge_offset.Set(0.0f, 0.5f, 2.5f);
	car.front_wing_size.Set(2.0f, 0.25f, 0.7f);
	car.front_wing_offset.Set(0.0f, 0.5f, 3.75f);
	car.rear_wing_size.Set(1.2f, 0.05f, 0.5f);
	car.rear_wing_offset.Set(0.0f, 1.25f, -1.25f);
	car.vertical_wing_size.Set(0.05f, 0.5f, 0.5);
	car.vertical_wing_offset.Set(0.6f, 1.2f, -1.25f);
	car.upper_size.Set(0.7f, 0.4f, 1.6f);
	car.upper_offset.Set(0.0f, 1.2f, -0.2f);
	car.mass = 350.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.6f;
	float half_length = car.chassis_size.z*1.2f;
	float rear_wheels = car.chassis_size.z * 0.6f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -rear_wheels + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -rear_wheels + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->collision_listeners.add(this);
	vehicle->SetPos(14, 0, 160);
	turboTimer = 0;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	delete[] vehicle->info.wheels;

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		if (slow == true)
		{
			vehicle->body->setLinearVelocity(vehicle->body->getLinearVelocity() / 1.01f);
		}
		acceleration = MAX_ACCELERATION;
	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if(turn < TURN_DEGREES)
			turn +=  TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if(turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		if (vehicle->GetKmh() > 0.0f)
			brake = BRAKE_POWER;

		else
		{
			if (slow == true)
			{
				vehicle->body->setLinearVelocity(vehicle->body->getLinearVelocity() / 1.01f);
			}
			acceleration = -MAX_ACCELERATION ;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		if ((jump_cooldown.Read() * 0.001) >= JUMP_COOLDOWN)
		{
			vehicle->Push(0.0f, JUMP_IMPULSE * 3, 0.0f);
			jump_cooldown.Start();

		}
	}

	if (turboTimer > 0)
	{
		acceleration = MAX_ACCELERATION * 3;
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();

	char title[80];
	sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(PhysBody3D* body1, PhysBody3D* body2) 
{
	//1-grass 2-turbo 3-checkpoints
	if (body2->id == 2)
	{
		slow = true;
	}
	else if (body2->id == 3)
	{
		/*if (turboSoundActive)
		{
			App->audio->PlayFx(turboFx);
			turboSoundActive = false;
		}*/
		turboTimer = 2;
	}
	else if (body2->id == 4 && App->scene_intro->checkpoints[0].wire == false)
	{
		if (App->scene_intro->passedCheckpoints == 2)
		{
			App->scene_intro->lap++;
			App->scene_intro->checkpoints[0].wire = true;
			//App->audio->PlayFx(metaFx);
			App->scene_intro->timer += 7;
			App->scene_intro->passedCheckpoints = 0;
			App->scene_intro->checkpoints[1].wire = false;
		}
	}
	else if (body2->id == 5 && App->scene_intro->checkpoints[1].wire == false)
	{
		//App->audio->PlayFx(checkpointFx);
		App->scene_intro->passedCheckpoints++;
		App->scene_intro->checkpoints[1].wire = true;
		App->scene_intro->timer += 7;
		App->scene_intro->checkpoints[2].wire = false;
	}
	else if (body2->id == 6 && App->scene_intro->checkpoints[2].wire == false)
	{
		//App->audio->PlayFx(checkpointFx);
		App->scene_intro->passedCheckpoints++;
		App->scene_intro->checkpoints[2].wire = true;
		App->scene_intro->timer += 7;
		App->scene_intro->checkpoints[0].wire = false;
	}
}



