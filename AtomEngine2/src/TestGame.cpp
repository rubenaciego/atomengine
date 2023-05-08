#include "TestGame.hpp"

void TestGame::Start()
{
	/*
	float fieldDepth = 10.0f;
	float fieldWidth = 10.0f;
		
	Vertex data[] = {
		Vertex(Vector3(-fieldWidth, 0.0f, -fieldDepth), Vector2(0.0f, 0.0f)),
		Vertex(Vector3(-fieldWidth, 0.0f, fieldDepth * 3), Vector2(0.0f, 1.0f)),
		Vertex(Vector3(fieldWidth * 3, 0.0f, -fieldDepth), Vector2(1.0f, 0.0f)),
		Vertex(Vector3(fieldWidth * 3, 0.0f, fieldDepth * 3), Vector2(1.0f, 1.0f))
	};
	
	unsigned int indices[] = {
		0, 1, 2,
		2, 1, 3
	};

	std::shared_ptr<Mesh> mesh = MeshManager::CreateMesh(data, sizeof(data) / sizeof(data[0]),
		indices, sizeof(indices) / sizeof(indices[0]), "Plane");

	std::shared_ptr<Texture> texture = TextureManager::CreateTexture("res/Textures/defaultTexture.png");
	std::shared_ptr<Texture> brick = TextureManager::CreateTexture("res/Textures/bricks2.jpg");
	std::shared_ptr<Texture> bricks_normal = TextureManager::CreateTexture("res/Textures/bricks2_normal.jpg");

	Material mat;
	mat.AddTexture("diffuse", texture);
	mat.AddFloat("specularIntensity", 1.0f);
	mat.AddFloat("specularPower", 8.0f);
	mat.AddFloat("dispScale", 0);
	mat.AddFloat("dispOffset", 0);

	Material bricks;
	bricks.AddTexture("diffuse", brick);
	bricks.AddTexture("normal", bricks_normal);
	bricks.AddFloat("specularIntensity", 1.0f);
	bricks.AddFloat("specularPower", 8.0f);
	bricks.AddFloat("dispScale", 0);
	bricks.AddFloat("dispOffset", 0);

	std::shared_ptr<Mesh> mesh2 = MeshManager::CreateMesh("res/Models/Metroid.obj");
	std::shared_ptr<Mesh> mesh3 = MeshManager::CreateMesh("res/Models/Model.obj");

	GameObject* planeObj = new GameObject();
	planeObj->AddComponent(new MeshRenderer(MeshManager::GetMesh("Plane"), bricks));
	planeObj->transform.position = Vector3(0, -1.0f, 5);

	GameObject* dirLight = new GameObject();
	dirLight->AddComponent(new DirectionalLight(Vector3::ONE, 0.4f));
	dirLight->transform.rotation = Quaternion(Vector3::RIGHT, ToRadians(-45));

	GameObject* pointLight = new GameObject();
	pointLight->AddComponent(new PointLight(Vector3::RIGHT, 0.8f, Vector3::FORWARD));
	pointLight->transform.position = Vector3(6, 0, 2);

	GameObject* spotLight = new GameObject();
	spotLight->AddComponent(new SpotLight(Vector3::UP, 0.8f, Vector3::FORWARD * 0.1f, 0.7f));
	spotLight->transform.position = Vector3(1, 0, 5);
	spotLight->transform.rotation = Quaternion(Vector3::UP, ToRadians(90));

	GameObject* camera = new GameObject();
	camera->AddComponent(new Camera(ToRadians(70), (float)engine->GetWidth()  / (float)engine->GetHeight(), 0.1f, 1000.0f));
	camera->AddComponent(new FreeLook(0.2f));
	camera->AddComponent(new FreeMove(10));

	GameObject* littlePlane = new GameObject();
	littlePlane->AddComponent(new MeshRenderer(mesh, mat));
	littlePlane->transform.scale /= 10.0f;
	littlePlane->transform.position.y = 2;
	littlePlane->transform.rotation = Quaternion(Vector3::UP, ToRadians(90.0f));

	GameObject* littlePlane2 = new GameObject();
	littlePlane2->AddComponent(new MeshRenderer(mesh, mat));
	littlePlane2->transform.position.z = 100;

	GameObject* monkey = new GameObject();
	monkey->AddComponent(new MeshRenderer(mesh3, mat));
	monkey->transform.position.z = 3;

	GameObject* metroid = new GameObject();
	metroid->AddComponent(new MeshRenderer(mesh2, mat));
	metroid->transform.position = Vector3(3, 2, 4);

	AddGameObject(dirLight);
	AddGameObject(planeObj);
	AddGameObject(littlePlane);
	AddGameObject(pointLight);
	AddGameObject(spotLight);
	AddGameObject(camera);
	AddGameObject(monkey);
	AddGameObject(metroid);

	littlePlane->AddChild(littlePlane2);*/
}

const char* TestGame::GetName()
{
	return "3D Engine";
}
