#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePhysics3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	ground = new Plane(0, 1, 0, 0);
	ground->axis = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	//143, 170, 60
	wall[0].SetPos(0, 0, 256);
	wall[0].size.x = 5;
	wall[0].size.y = 512;
	wall[0].size.z = 512;
	wall[0].axis = false;
	wall[0].color = Green;
	App->physics->AddBody(wall[0], this , 0, false);

	wall[1].SetPos(512, 0, 256);
	wall[1].size.x = 5;
	wall[1].size.y = 512;
	wall[1].size.z = 512;
	wall[1].axis = false;
	wall[1].color = Green;
	App->physics->AddBody(wall[1], this, 0, false);

	wall[2].SetPos(256, 0, 0);
	wall[2].size.x = 512;
	wall[2].size.y = 512;
	wall[2].size.z = 5;
	wall[2].axis = false;
	wall[2].color = Green;
	App->physics->AddBody(wall[2], this, 0, false);

	wall[3].SetPos(256, 0, 512);
	wall[3].size.x = 512;
	wall[3].size.y = 512;
	wall[3].size.z = 5;
	wall[3].axis = false;
	wall[3].color = Green;
	App->physics->AddBody(wall[3], this, 0, false);

	borders[0].SetPos(0, 1, 256);
	borders[0].size.x = 9;
	borders[0].size.y = 6;
	borders[0].size.z = 512;
	borders[0].axis = false;
	borders[0].color.Set(255, 0, 0);
	App->physics->AddBody(borders[0], this, 0, false);

	borders[1].SetPos(512, 1, 256);
	borders[1].size.x = 9;
	borders[1].size.y = 6;
	borders[1].size.z = 512;
	borders[1].axis = false;
	borders[1].color.Set(255, 0, 0);
	App->physics->AddBody(borders[1], this, 0, false);

	borders[2].SetPos(256, 1, 0);
	borders[2].size.x = 512;
	borders[2].size.y = 6;
	borders[2].size.z = 9;
	borders[2].axis = false;
	borders[2].color.Set(255, 0, 0);
	App->physics->AddBody(borders[2], this, 0, false);

	borders[3].SetPos(256, 1, 512);
	borders[3].size.x = 512;
	borders[3].size.y = 6;
	borders[3].size.z = 9;
	borders[3].axis = false;
	borders[3].color.Set(255, 0, 0);
	App->physics->AddBody(borders[3], this, 0, false);

	//race track 
	map[0].SetPos(0, -4, 0);
	map[0].size.x = 1200;
	map[0].size.y = 10;
	map[0].size.z = 1200;
	map[0].axis = false;
	map[0].color = Black;
	App->physics->AddBody(map[0], this, 0, false);
	
	map[1].SetPos(25, 0, 115);
	map[1].size.x = 2;
	map[1].size.y = 60;
	map[1].size.z = 160;
	map[1].axis = false;
	map[1].color = White;
	App->physics->AddBody(map[1], this, 0, false);

	map[2].SetPos(47, 0, 194);
	map[2].size.x = 45;
	map[2].size.y = 60;
	map[2].size.z = 2;
	map[2].axis = false;
	map[2].color = White;
	App->physics->AddBody(map[2], this, 0, false);

	map[3].SetPos(25, 0, 224);
	map[3].size.x = 45;
	map[3].size.y = 60;
	map[3].size.z = 2;
	map[3].axis = false;
	map[3].color = White;
	App->physics->AddBody(map[3], this, 0, false);

	map[4].SetPos(68.5, 0, 324);
	map[4].size.x = 2;
	map[4].size.y = 60;
	map[4].size.z = 260;
	map[4].axis = false;
	map[4].color = White;
	App->physics->AddBody(map[4], this, 0, false);
	
	map[5].SetPos(48.5, 0, 273);
	map[5].size.x = 2;
	map[5].size.y = 60;
	map[5].size.z = 100;
	map[5].axis = false;
	map[5].color = White;
	App->physics->AddBody(map[5], this, 0, false);
	
	map[6].SetPos(25, 0, 322);
	map[6].size.x = 45;
	map[6].size.y = 60;
	map[6].size.z = 2;
	map[6].axis = false;
	map[6].color = White;
	App->physics->AddBody(map[6], this, 0, false);

	map[7].SetPos(111, 0, 455);
	map[7].size.x = 87;
	map[7].size.y = 60;
	map[7].size.z = 2;
	map[7].axis = false;
	map[7].color = White;
	App->physics->AddBody(map[7], this, 0, false);

	//grass
	grass[0].SetPos(65.5, 2.0, 324);
	grass[0].size.x = 5;
	grass[0].size.y = 0.4;
	grass[0].size.z = 260;
	grass[0].axis = false;
	grass[0].wire = false;
	grass[0].color = Yellow;
	physSensor = App->physics->AddBody(grass[0], this, 0, true);
	physSensor->SetId(8);

	grass[1].SetPos(51.5, 2.0, 273);
	grass[1].size.x = 5;
	grass[1].size.y = 0.4;
	grass[1].size.z = 100;
	grass[1].axis = false;
	grass[1].wire = false;
	grass[1].color = Yellow;
	physSensor = App->physics->AddBody(grass[1], this, 0, true);
	physSensor->SetId(8);

	grass[2].SetPos(24, 2.0, 418);
	grass[2].size.x = 40;
	grass[2].size.y = 0.4;
	grass[2].size.z = 192;
	grass[2].axis = false;
	grass[2].wire = false;
	grass[2].color = Yellow;
	physSensor = App->physics->AddBody(grass[2], this, 0, true);
	physSensor->SetId(8);

	//ramps
	ramp[0].SetPos(275, 1, 473);
	ramp[0].SetRotation(20.0f, { 1,0,0 });
	ramp[0].size.x = 250;
	ramp[0].size.y = 2;
	ramp[0].size.z = 20;
	ramp[0].axis = false;
	ramp[0].color = White;
	App->physics->AddBody(ramp[0], this, 0, false);

	ramp[1].SetPos(275, 5, 465);
	ramp[1].SetRotation(40.0f, { 1,0,0 });
	ramp[1].size.x = 250.1;
	ramp[1].size.y = 2;
	ramp[1].size.z = 20;
	ramp[1].axis = false;
	ramp[1].color = White;
	App->physics->AddBody(ramp[1], this, 0, false);

	ramp[2].SetPos(275, 21, 454);
	ramp[2].SetRotation(80.0f, { 1,0,0 });
	ramp[2].size.x = 250.1;
	ramp[2].size.y = 2;
	ramp[2].size.z = 20;
	ramp[2].axis = false;
	ramp[2].color = White;
	App->physics->AddBody(ramp[2], this, 0, false);

	ramp[3].SetPos(275, 36, 454);
	ramp[3].SetRotation(100.0f, { 1,0,0 });
	ramp[3].size.x = 250;
	ramp[3].size.y = 2;
	ramp[3].size.z = 20;
	ramp[3].axis = false;
	ramp[3].color = White;
	App->physics->AddBody(ramp[3], this, 0, false);

	ramp[4].SetPos(275, 46, 459);
	ramp[4].SetRotation(120.0f, { 1,0,0 });
	ramp[4].size.x = 250.1;
	ramp[4].size.y = 2;
	ramp[4].size.z = 20;
	ramp[4].axis = false;
	ramp[4].color = White;
	App->physics->AddBody(ramp[4], this, 0, false);

	ramp[5].SetPos(275, 52, 465);
	ramp[5].SetRotation(140.0f, { 1,0,0 });
	ramp[5].size.x = 250;
	ramp[5].size.y = 2;
	ramp[5].size.z = 20;
	ramp[5].axis = false;
	ramp[5].color = White;
	App->physics->AddBody(ramp[5], this, 0, false);

	ramp[6].SetPos(275, 55, 471);
	ramp[6].SetRotation(160.0f, { 1,0,0 });
	ramp[6].size.x = 250.1;
	ramp[6].size.y = 2;
	ramp[6].size.z = 20;
	ramp[6].axis = false;
	ramp[6].color = White;
	App->physics->AddBody(ramp[6], this, 0, false);

	ramp[7].SetPos(275, 57, 479);
	ramp[7].SetRotation(180.0f, { 1,0,0 });
	ramp[7].size.x = 250;
	ramp[7].size.y = 2;
	ramp[7].size.z = 20;
	ramp[7].axis = false;
	ramp[7].color = White;
	App->physics->AddBody(ramp[7], this, 0, false);

	ramp[8].SetPos(275, 1, 491);
	ramp[8].SetRotation(-20.0f, { 1,0,0 });
	ramp[8].size.x = 250;
	ramp[8].size.y = 2;
	ramp[8].size.z = 20;
	ramp[8].axis = false;
	ramp[8].color = White;
	App->physics->AddBody(ramp[8], this, 0, false);

	ramp[9].SetPos(275, 5, 497);
	ramp[9].SetRotation(-40.0f, { 1,0,0 });
	ramp[9].size.x = 250.1;
	ramp[9].size.y = 2;
	ramp[9].size.z = 20;
	ramp[9].axis = false;
	ramp[9].color = White;
	App->physics->AddBody(ramp[9], this, 0, false);

	ramp[10].SetPos(275, 11, 503);
	ramp[10].SetRotation(-60.0f, { 1,0,0 });
	ramp[10].size.x = 250;
	ramp[10].size.y = 2;
	ramp[10].size.z = 20;
	ramp[10].axis = false;
	ramp[10].color = White;
	App->physics->AddBody(ramp[10], this, 0, false);

	ramp[11].SetPos(275, 21, 508);
	ramp[11].SetRotation(-80.0f, { 1,0,0 });
	ramp[11].size.x = 250.1;
	ramp[11].size.y = 2;
	ramp[11].size.z = 20;
	ramp[11].axis = false;
	ramp[11].color = White;
	App->physics->AddBody(ramp[11], this, 0, false);

	ramp[12].SetPos(275, 36, 508);
	ramp[12].SetRotation(-100.0f, { 1,0,0 });
	ramp[12].size.x = 250;
	ramp[12].size.y = 2;
	ramp[12].size.z = 20;
	ramp[12].axis = false;
	ramp[12].color = White;
	App->physics->AddBody(ramp[12], this, 0, false);

	ramp[13].SetPos(275, 46, 503);
	ramp[13].SetRotation(-120.0f, { 1,0,0 });
	ramp[13].size.x = 250.1;
	ramp[13].size.y = 2;
	ramp[13].size.z = 20;
	ramp[13].axis = false;
	ramp[13].color = White;
	App->physics->AddBody(ramp[13], this, 0, false);

	ramp[14].SetPos(275, 52, 497);
	ramp[14].SetRotation(-140.0f, { 1,0,0 });
	ramp[14].size.x = 250;
	ramp[14].size.y = 2;
	ramp[14].size.z = 20;
	ramp[14].axis = false;
	ramp[14].color = White;
	App->physics->AddBody(ramp[14], this, 0, false);

	ramp[15].SetPos(275, 55, 491);
	ramp[15].SetRotation(-160.0f, { 1,0,0 });
	ramp[15].size.x = 250.1;
	ramp[15].size.y = 2;
	ramp[15].size.z = 20;
	ramp[15].axis = false;
	ramp[15].color = White;
	App->physics->AddBody(ramp[15], this, 0, false);

	ramp[16].SetPos(275, 11, 459);
	ramp[16].SetRotation(60.0f, { 1,0,0 });
	ramp[16].size.x = 250;
	ramp[16].size.y = 2;
	ramp[16].size.z = 20;
	ramp[16].axis = false;
	ramp[16].color = White;
	App->physics->AddBody(ramp[16], this, 0, false);

	ramp[17].SetPos(230, 0, 482);
	ramp[17].size.x = 3;
	ramp[17].size.y = 40;
	ramp[17].size.z = 50;
	ramp[17].axis = false;
	ramp[17].color = White;
	App->physics->AddBody(ramp[17], this, 0, false);

	ramp[18].SetPos(295, 15, 500);
	ramp[18].size.x = 3;
	ramp[18].size.y = 80;
	ramp[18].size.z = 50;
	ramp[18].axis = false;
	ramp[18].color = White;
	App->physics->AddBody(ramp[18], this, 0, false);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	ground->Render();

	for (int i = 0; i < 4; i++)
	{
		wall[i].Render();
	}

	for (int i = 0; i < 4; i++)
	{
		borders[i].Render();
	}

	for (int i = 0; i < 20; i++)
	{
		map[i].Render();
	}

	for (int i = 0; i < 10; i++)
	{
		grass[i].Render();
	}

	for (int i = 0; i < 40; i++)
	{
		ramp[i].Render();
	}

	if (frames % 60 == 0 && timer > 0 && App->camera->finish == false)
	{
		if (App->player->turboTimer > 0)
		{
			App->player->turboTimer--;
		}
		timer--;
	}
	frames++;

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

