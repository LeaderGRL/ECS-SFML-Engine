#include "pch.h"
#include "Application.h"
#include "Entity.h"
#include "EntityManager.h"
#include "CameraComponent.h"
#include <SFML/Window.hpp>
#include <filesystem>
#include "LuaAPI.h"
#include "NetworkManager.h"
#include "SceneManager.h"
#include "ScriptComponent.h"

namespace LeaderEngine {

	Application::Application() //: window(sf::VideoMode(800, 600), "ECS Application")
	{
		//luabridge::getGlobalNamespace()
		Init();
		Run();
	}

	Application::~Application()
	{
		window.close();
	}

	sf::RenderWindow& Application::GetWindow()
	{
		return window;
	}

	void Application::Init()
	{

		ResourceManager::GetInstance().LoadResource("Assets/Config/resources.yml");

		LuaAPI::GetInstance().CPP_To_LUA();

	/*	tgui::EditBox::Ptr editBox = tgui::EditBox::create();
		editBox->setPosition(100, 100);
		gui.add(editBox);
		editBox->onReturnKeyPress.connect([editBox]()
		{
						std::cout << "You entered: " << editBox->getText().to << std::endl;
		});*/


		luabridge::setGlobal(LuaAPI::GetInstance().GetLuaState(), &gui, "gui");
		luabridge::setGlobal(LuaAPI::GetInstance().GetLuaState(), &window, "window");

		LuaAPI::GetInstance().LoadScript("Assets/Scripts/Config.lua");

		std::unique_ptr<Scene> mainScene = std::make_unique<Scene>();
		SceneManager::GetInstance().PushScene(std::move(mainScene));

		Entity* mainMenu = SceneManager::GetInstance().GetCurrentScene()->GetEntityManager().CreateEntity("MainMenu");
		mainMenu->AddComponent<ScriptComponent, const char*>("Assets/Scripts/MainMenu.lua");
		/*Entity* bulletManager = EntityManager::GetInstance().CreateEntity("BulletManager");
		bulletManager->AddComponent<ScriptComponent, const char*>("Assets/Scripts/BulletManager.lua");*/
		//Entity* camera = SceneManager::GetInstance().GetCurrentScene()->GetEntityManager().CreateEntity("MainCamera");
		//camera->AddComponent<ScriptComponent, const char*>("Assets/Scripts/Camera.lua");
		/*Entity* bullets = EntityManager::GetInstance().CreateEntity("Rocket");
		bullets->AddComponent<ScriptComponent, const char*>("Assets/Scripts/Bullets.lua");*/
		//Entity* weapons = EntityManager::GetInstance().CreateEntity("FighterWeapons");
		//weapons->AddComponent<ScriptComponent, const char*>("Assets/Scripts/Weapons.lua");
		//Entity* player = EntityManager::GetInstance().CreateEntity("Fighter");
		//player->AddComponent<ScriptComponent, const char*>("Assets/Scripts/Player.lua"); // Load the script automaticaly

		//window.setView(camera->GetComponent<CameraComponent>()->getView());

	}  
	
	void Application::Run()
	{
		sf::Clock clock;
		sf::Event event;

		SceneManager::GetInstance().GetCurrentScene()->Init();

		while (window.isOpen())
		{
			//sf::Time time = clock.getElapsedTime();
			sf::Time time = clock.restart();
			//window.setView(SceneManager::GetInstance().GetCurrentScene()->GetEntityManager().GetEntity("MainCamera")->GetComponent<CameraComponent>()->getView());

			while (window.pollEvent(event))
			{
				gui.handleEvent(event);

				switch (event.type)
				{
					// "close requested" event: we close the window
					case sf::Event::Closed:
						window.close();
						break;
					case sf::Event::KeyPressed:
						EventManager::GetInstance().InvokeEvent(INPUT_EVENT::KeyPressed, event);
						break;
					case sf::Event::KeyReleased:
						EventManager::GetInstance().InvokeEvent(INPUT_EVENT::KeyReleased, event);
						break;
					case sf::Event::MouseButtonPressed:
						EventManager::GetInstance().InvokeEvent(INPUT_EVENT::MouseButtonPressed, event);
						break;
					case sf::Event::MouseButtonReleased:
						EventManager::GetInstance().InvokeEvent(INPUT_EVENT::MouseButtonReleased, event);
						break;
				}
			}

			window.clear(sf::Color::Black);
			gui.draw();
			SceneManager::GetInstance().GetCurrentScene()->Draw(window, sf::RenderStates::Default);
			SceneManager::GetInstance().Update(time.asSeconds());
			NetworkManager::GetInstance().Update();
			/*SceneManager::GetInstance().GetCurrentScene()->GetEntityManager().draw(window, sf::RenderStates::Default);
			SceneManager::GetInstance().GetCurrentScene()->GetEntityManager().Update(time.asSeconds());*/
			window.display();
		}
	}

	void Application::Close()
	{
		window.close();
	}

}

