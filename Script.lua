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
    print(event.key.code)
    print(Keyboard.KEY_Z)
    if event.key.code == Keyboard.KEY_Z then
       Move(0,1) 
    end
end

function Move(x, y)
    player:Move(x,y)
end

EventManager:GetInstance():RegisterEvent(LeaderEngine.INPUT_EVENT_KEY_PRESSED, OnKeyPressed)

--print(OnKeyPressed())

