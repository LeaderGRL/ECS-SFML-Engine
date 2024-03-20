#include "pch.h"
#include "LuaAPI.h"

#include <TGUI/Backends/SFML.hpp>
#include <TGUI/Widgets/EditBox.hpp>

#include "NetworkingComponent.h"
#include "Scene.h"
#include "SceneManager.h"


namespace LeaderEngine 
{	
	LuaAPI::LuaAPI()
	{

	}

	LuaAPI::~LuaAPI()
	{
		lua_close(L);
		free(L);
	}

	LuaAPI& LuaAPI::GetInstance()
	{
		static LuaAPI instance;
		return instance;
	}

	void LuaAPI::CPP_To_LUA()
	{
		L = luaL_newstate();
		luaL_openlibs(L);

		luabridge::getGlobalNamespace(L)
			.beginClass<sf::RenderWindow>("RenderWindow")
			.addFunction("isOpen", &sf::RenderWindow::isOpen)
			.addFunction("clear", &sf::RenderWindow::clear)
			.addFunction("display", &sf::RenderWindow::display)
			.addFunction("pollEvent", &sf::RenderWindow::pollEvent)
			.addFunction("close", &sf::RenderWindow::close)
			.addFunction("setView", &sf::RenderWindow::setView)
			.addFunction("getView", &sf::RenderWindow::getView)
			.addFunction("setMouseCursorVisible", &sf::RenderWindow::setMouseCursorVisible)
			.addFunction("setFramerateLimit", &sf::RenderWindow::setFramerateLimit)
			.addFunction("setVerticalSyncEnabled", &sf::RenderWindow::setVerticalSyncEnabled)
			.addFunction("setKeyRepeatEnabled", &sf::RenderWindow::setKeyRepeatEnabled)
			.addFunction("setActive", &sf::RenderWindow::setActive)
			.addFunction("getSize", &sf::RenderWindow::getSize)
			.endClass();
			

		luabridge::getGlobalNamespace(L)
			.beginClass<Entity>("Entity")
			.addConstructor<void(*) (void)>()
			.addFunction("GetId", &Entity::GetId)
			.addFunction("AddSprite2DComponent", &Entity::AddComponent<Sprite2DComponent>)
			.addFunction("GetSprite2DComponent", &Entity::GetComponent<Sprite2DComponent>)
			.addFunction("AddAnimation2DComponent", &Entity::AddComponent<Animation2DComponent>)
			.addFunction("GetAnimation2DComponent", &Entity::GetComponent<Animation2DComponent>)
			//.addFunction("AddAnimation2DComponent", &Entity::AddComponent<Animation2DComponent(std::string name, bool loop)>)
			.addFunction("AddAnimation2DComponent", [](Entity* entity, const std::string& name, bool loop, bool animating) { // Lambda function to add Animation2DComponent with parameters
				entity->AddComponent<Animation2DComponent>(name, loop, animating);
			})
			.addFunction("AddScriptComponent", &Entity::AddComponent<ScriptComponent>)
			.addFunction("GetScriptComponent", &Entity::GetComponent<ScriptComponent>)
			.addFunction("AddCameraComponent", &Entity::AddComponent<CameraComponent>)
			.addFunction("GetCameraComponent", &Entity::GetComponent<CameraComponent>)
			.addFunction("AddBoxColliderComponent", &Entity::AddComponent<BoxColliderComponent>)
			.addFunction("GetBoxColliderComponent", &Entity::GetComponent<BoxColliderComponent>)
			.addFunction("AddNetworkingComponent", &Entity::AddComponent<NetworkingComponent>)
			.addFunction("GetNetworkComponent", &Entity::GetComponent<NetworkingComponent>)
		/*	.addFunction("AddComponent", static_cast<void (Entity::*)(int)>(&Entity::AddComponent))
			.addFunction("GetComponent", static_cast<luabridge::LuaRef(Entity::*)(int)>(&Entity::GetComponent))*/
			.addFunction("GetPosition", (&sf::Transformable::getPosition))
			.addFunction("SetPosition", static_cast<void (sf::Transformable::*)(float, float)>(&sf::Transformable::setPosition))
			.addFunction("SetParent", &Entity::SetParent)
			.addFunction("GetParent", &Entity::GetParent)
			.addFunction("AddChild", &Entity::AddChild)
			.addFunction("GetChild", &Entity::GetChild)
			.addFunction("Move_F", static_cast<void (sf::Transformable::*)(float, float)>(&sf::Transformable::move))
			.addFunction("Move_V", static_cast<void (sf::Transformable::*)(const sf::Vector2f&)>(&sf::Transformable::move))
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginClass<EventManager>("EventManager")
			.addStaticFunction("GetInstance", &EventManager::GetInstance)
			.addFunction("RegisterEvent", static_cast<void (EventManager::*)(int, const luabridge::LuaRef&)>(&EventManager::RegisterEvent))
			.addFunction("UnregisterEvent", &EventManager::UnregisterEvent)
			.addFunction("InvokeEvent", &EventManager::InvokeEvent)
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginClass<EntityManager>("EntityManager")
			.addFunction("CreateEntity", &EntityManager::CreateEntity)
			.addFunction("GetEntity", &EntityManager::GetEntity)
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginClass<SceneManager>("SceneManager")
			.addStaticFunction("GetInstance", &SceneManager::GetInstance)
			//.addFunction("PushScene", &SceneManager::PushScene)
			.addFunction("PopScene", &SceneManager::PopScene)
			.addFunction("ChangeScene", static_cast<void (SceneManager::*)(Scene*)>(&SceneManager::ChangeScene))
			.addFunction("GetCurrentScene", &SceneManager::GetCurrentScene)
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginClass<Scene>("Scene")
			.addFunction("GetEntityManager", &Scene::GetEntityManager)
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginClass<sf::Drawable>("Drawable")
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginClass<IComponent>("IComponent")
			.endClass()
			.deriveClass<IDrawableComponent, IComponent>("IDrawableComponent")
			.endClass()
			.deriveClass<Sprite2DComponent, IDrawableComponent>("Sprite2DComponent")
			.addConstructor<void(*) (void)>()
			.addFunction("SetSprite", &Sprite2DComponent::SetSprite)
			.addFunction("SetSpriteByName", &Sprite2DComponent::SetSpriteByName)
			.addFunction("GetSprite", &Sprite2DComponent::GetSprite)
			.addFunction("SetSize", &Sprite2DComponent::SetSize)
			//.addFunction("PlayAnimation", &Sprite2DComponent::PlayAnimation)
			//.addFunction("StopAnimation", &Sprite2DComponent::StopAnimation)
			.endClass()
			.deriveClass<CameraComponent, IComponent>("CameraComponent")
			.addFunction("SetView", &CameraComponent::setView)
			.addFunction("GetView", &CameraComponent::getView)
			.addFunction("SetSize", &CameraComponent::setSize)
			.addFunction("GetSize", &CameraComponent::getSize)
			.addFunction("SetZoom", &CameraComponent::setZoom)
			.addFunction("GetZoom", &CameraComponent::getZoom)
			.addFunction("SetRotation", &CameraComponent::setRotation)
			.addFunction("GetRotation", &CameraComponent::getRotation)
			.endClass()
			.deriveClass<ColliderComponent, IComponent>("ColliderComponent")
			.endClass()
			.deriveClass<BoxColliderComponent, ColliderComponent>("BoxColliderComponent")
			.addConstructor<void(*) (sf::Vector2f)>()
			.addFunction("SetSize", &BoxColliderComponent::SetSize)
			.endClass()
			.deriveClass<ScriptComponent, IComponent>("ScriptComponent")
			.addFunction("LoadScript", &ScriptComponent::LoadScript)
			.endClass()
			.deriveClass<Animation2DComponent, Sprite2DComponent>("Animation2DComponent")
			.addConstructor<void(*) (void)>()
			.addConstructor<void(*) (const std::string&, bool)>()
			.addFunction("PlayAnimation", &Animation2DComponent::PlayAnimation)
			.addFunction("StopAnimation", &Animation2DComponent::StopAnimation)
			.addFunction("GetAnimationName", &Animation2DComponent::GetAnimationName)
			.addFunction("SetAnimationName", &Animation2DComponent::SetAnimationName)
			.endClass()
			.deriveClass<NetworkingComponent, IComponent>("NetworkingComponent")
			.endClass();


		luabridge::getGlobalNamespace(L)
			.beginClass<ResourceManager>("ResourceManager")
			.addStaticFunction("GetInstance", &ResourceManager::GetInstance)
			.addFunction("GetTexture", &ResourceManager::getTexture)
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginClass<sf::Texture>("Texture")
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginClass<sf::Vector2f>("Vector2f")
			.addConstructor<void(*) (float, float)>()
			.addProperty("x", &sf::Vector2f::x)
			.addProperty("y", &sf::Vector2f::y)
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginClass<sf::Vector2u>("Vector2u")
			.addConstructor<void(*) (unsigned int, unsigned int)>()
			.addProperty("x", &sf::Vector2u::x)
			.addProperty("y", &sf::Vector2u::y)
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginClass<sf::Vector2i>("Vector2i")
			.addConstructor<void(*) (int, int)>()
			.addProperty("x", &sf::Vector2i::x)
			.addProperty("y", &sf::Vector2i::y)
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginClass<sf::Sprite>("Sprite")
			.addConstructor<void(*) (void)>()
			.addFunction("setPosition", static_cast<void (sf::Sprite::*)(float, float)>(&sf::Sprite::setPosition))
			.addFunction("setColor", &sf::Sprite::setColor)
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginNamespace("Input")
			.beginClass<INPUT_EVENT>("INPUT_EVENT")
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginNamespace("Input")
			.addVariable("INPUT_EVENT_KEY_PRESSED", INPUT_EVENT::KeyPressed)
			.addVariable("INPUT_EVENT_KEY_RELEASED", INPUT_EVENT::KeyReleased)
			.addVariable("INPUT_EVENT_MOUSE_PRESSED", INPUT_EVENT::MouseButtonPressed)
			.addVariable("INPUT_EVENT_MOUSE_RELEASED", INPUT_EVENT::MouseButtonReleased)
			.endNamespace();

		luabridge::getGlobalNamespace(L)
			.beginNamespace("Component")
			.addVariable("SPRITE2D", COMPONENT_TYPE::SPRITE2D)
			.addVariable("BOX_COLLIDER", COMPONENT_TYPE::BOX_COLLIDER)
			.addVariable("ANIMATION", COMPONENT_TYPE::ANIMATION)
			.addVariable("CAMERA", COMPONENT_TYPE::CAMERA)
			.addVariable("SCRIPT", COMPONENT_TYPE::SCRIPT)
			.endNamespace();

		luabridge::getGlobalNamespace(L)
			.beginNamespace("sf")
			.beginClass<sf::Event>("Event")
			.addConstructor<void(*) (void)>()
			.addProperty("type", &sf::Event::type)
			//.addProperty("KeyPressed", sf::Event::KeyPressed)
			.addProperty("key", &sf::Event::key)
			.addProperty("mouseButton", &sf::Event::mouseButton)
			.endClass();


		luabridge::getGlobalNamespace(L)
			.beginNamespace("sf")
			.addVariable("Closed", sf::Event::EventType::Closed)
			.addVariable("KeyPressed", sf::Event::EventType::KeyPressed)
			.addVariable("KeyReleased", sf::Event::EventType::KeyReleased)
			.addVariable("MouseButtonPressed", sf::Event::EventType::MouseButtonPressed)
			.addVariable("MouseButtonReleased", sf::Event::EventType::MouseButtonReleased)
			.endNamespace();

		luabridge::getGlobalNamespace(L)
			.beginNamespace("sf")
			.beginClass<sf::Keyboard::Key>("Key")
			.endClass()
			.addVariable("KEY_A", sf::Keyboard::Key::A)
			.addVariable("KEY_B", sf::Keyboard::Key::B)
			.addVariable("KEY_C", sf::Keyboard::Key::C)
			.addVariable("KEY_D", sf::Keyboard::Key::D)
			.addVariable("KEY_E", sf::Keyboard::Key::E)
			.addVariable("KEY_F", sf::Keyboard::Key::F)
			.addVariable("KEY_G", sf::Keyboard::Key::G)
			.addVariable("KEY_H", sf::Keyboard::Key::H)
			.addVariable("KEY_I", sf::Keyboard::Key::I)
			.addVariable("KEY_J", sf::Keyboard::Key::J)
			.addVariable("KEY_K", sf::Keyboard::Key::K)
			.addVariable("KEY_L", sf::Keyboard::Key::L)
			.addVariable("KEY_M", sf::Keyboard::Key::M)
			.addVariable("KEY_N", sf::Keyboard::Key::N)
			.addVariable("KEY_O", sf::Keyboard::Key::O)
			.addVariable("KEY_P", sf::Keyboard::Key::P)
			.addVariable("KEY_Q", sf::Keyboard::Key::Q)
			.addVariable("KEY_R", sf::Keyboard::Key::R)
			.addVariable("KEY_S", sf::Keyboard::Key::S)
			.addVariable("KEY_T", sf::Keyboard::Key::T)
			.addVariable("KEY_U", sf::Keyboard::Key::U)
			.addVariable("KEY_V", sf::Keyboard::Key::V)
			.addVariable("KEY_W", sf::Keyboard::Key::W)
			.addVariable("KEY_X", sf::Keyboard::Key::X)
			.addVariable("KEY_Y", sf::Keyboard::Key::Y)
			.addVariable("KEY_Z", sf::Keyboard::Key::Z)
			.endNamespace();

		luabridge::getGlobalNamespace(L)
			.beginNamespace("sf")
			.beginClass<sf::Mouse::Button>("Button")
			.endClass()
			.addVariable("LEFT", sf::Mouse::Left)
			.addVariable("RIGHT", sf::Mouse::Right)
			.endNamespace();

		luabridge::getGlobalNamespace(L)
			.beginNamespace("sf")
			.beginClass<sf::Event::KeyEvent>("KeyEvent")
			.addStaticFunction("GetKeyEventCode", &Utils::GetKeyEventCode)
			//.addProperty("code", static_cast<int>(&sf::Event::KeyEvent::code), false)
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginNamespace("sf")
			.beginClass<sf::Event::MouseButtonEvent>("MouseButtonEvent")
			.addStaticFunction("GetMouseEventCode", &Utils::GetMouseEventCode)
			//.addProperty("code", static_cast<int>(&sf::Event::KeyEvent::code), false)
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginClass<sf::Rect<float>>("FloatRect")
			.addConstructor<void(*)(float, float, float, float)>()
			.addStaticFunction("intersects", &Utils::RectIntersects)
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginClass<Utils>("Gui")
			.addStaticFunction("AddWidget", &Utils::GuiAddWidget)
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginNamespace("tgui")
			.beginClass<tgui::GuiSFML>("Gui")
			.addFunction("Add", &tgui::GuiSFML::add)
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginNamespace("tgui")
			.beginClass<tgui::String>("String")
			.addConstructor<void(*) (const std::string&)>()
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginNamespace("tgui")
			.beginClass<tgui::EditBox>("EditBox")
			.addFunction("SetPosition", static_cast<void (tgui::EditBox::*)(tgui::Layout x, tgui::Layout y)>(&tgui::EditBox::setPosition))
			.addFunction("SetSize", static_cast<void (tgui::EditBox::*)(tgui::Layout width, tgui::Layout height)>(&tgui::EditBox::setSize))
			.addFunction("SetText", &tgui::EditBox::setText)
			.addFunction("GetText", &tgui::EditBox::getText)
			.addStaticFunction("Create", &tgui::EditBox::create)
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginNamespace("tgui")
			.beginClass<tgui::Layout>("Layout")
			.addConstructor<void(*) (float)>()
			.addConstructor<void(*) (const std::string&)>()
			.addFunction("getValue", &tgui::Layout::getValue)
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginClass<tgui::Widget>("Widget")
			.addFunction("SetPosition", static_cast<void (tgui::Widget::*)(tgui::Layout x, tgui::Layout y)>(&tgui::Widget::setPosition))
			.addFunction("SetSize", static_cast<void (tgui::Widget::*)(tgui::Layout width, tgui::Layout height)>(&tgui::Widget::setSize))
			.endClass()
			.deriveClass<tgui::ClickableWidget, tgui::Widget>("ClickableWidget")
			.endClass()
			.deriveClass<tgui::EditBox, tgui::ClickableWidget>("EditBox")
			.endClass();


		//const int scriptLoadStatus = luaL_dofile(L, "../LeaderEngine/Script.lua"); // Load the script
		//report_errors(L, scriptLoadStatus);

		//EventManager::GetInstance().
	}

	void LuaAPI::LoadScript(const char* path)
	{
		const int scriptLoadStatus = luaL_dofile(L, path);
		report_errors(L, scriptLoadStatus);
	}

	void LuaAPI::GetLuaStack()
	{
		int stack = lua_gettop(L);
		std::cout << "STACK : " << stack << std::endl;
	}

	lua_State* LuaAPI::GetLuaState()
	{
		return L;
	}

	void LuaAPI::report_errors(lua_State* luaState, int status)
	{
		if (status == 0) {
			return;
		}

		std::cerr << "[LUA ERROR] " << lua_tostring(luaState, -1) << std::endl;

		// remove error message from Lua state
		lua_pop(luaState, 1);
	}
	
	bool LuaAPI::Call_Errors(lua_State* luaState, const luabridge::LuaRef& func, int nbArgs, int nbReturnValue)
	{
		if (!func.isFunction())
			return false;

		//func.push(); // Push the Lua function onto the stack

		if (lua_pcall(luaState, nbArgs, nbReturnValue, 0) != 0) // Call the function
		{
			std::cerr << "Lua error: " << lua_tostring(func.state(), -1) << std::endl;
			lua_pop(func.state(), 1);  // pop the error message from the stack
			return false;
		}
		
		//lua_gc(L, LUA_GCCOLLECT, 0);

		return true;
	}

	void LuaAPI::CallFunction(const std::string& funcName)
	{
		lua_getglobal(L, funcName.c_str());
		if (lua_isfunction(L, -1))
		{
			if (lua_pcall(L, 0, 0, 0) != 0)
			{
				std::cerr << lua_tostring(L, -1) << std::endl;
				lua_pop(L, 1); // remove error message
			}
		}
		else
		{
			lua_pop(L, 1); // remove non-function value
		}
	}

}
