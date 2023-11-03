local EManager = EntityManager:GetInstance()
EManager:CreateEntity("Player")
local player = EManager:GetEntity("Player")
local fighter = Sprite2DComponent()
local fighterCollider = BoxColliderComponent(Vector2f(64,64))
local RManager = ResourceManager:GetInstance()
fighter:SetSprite(RManager:GetTexture("Fighter"))
player:AddComponent(fighter)
player:AddComponent(fighterCollider)
player:SetPosition(200,200)

function OnKeyPressed(event)
--    print(sf.KeyEvent.GetKeyEventCode(event.key))
--    print("Keyboard.KEY_Z:", sf.KEY_Z)

    if sf.KeyEvent.GetKeyEventCode(event.key) == sf.KEY_Z then
       print("test3")
       Move(0,-1) 
    end
end

function Move(x, y)
    print(player)
    player:Move(x,y)
end

EventManager:GetInstance():RegisterEvent(LeaderEngine.INPUT_EVENT_KEY_PRESSED, OnKeyPressed)

--print(OnKeyPressed())

