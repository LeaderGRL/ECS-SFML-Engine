local Player = {
    entityName = "Player",
    i = 0,
    EManager = EntityManager:GetInstance(),
    RManager = ResourceManager:GetInstance(),
    EventManager = EventManager:GetInstance(),
}

function Player:Create()
    local player = self.EManager:CreateEntity(self.entityName)
    --local player = self.EManager:GetEntity(self.entityName)
    --local fighter = Sprite2DComponent()
    --local fighterCollider = BoxColliderComponent(Vector2f(64,64))
    --fighter:SetSprite(self.RManager:GetTexture("Fighter"))
    player:AddComponent(Component.SPRITE2D)
    local fighter = player:GetComponent(Component.SPRITE2D)
    print(fighter)
    if fighter then
        fighter:SetSprite(self.RManager:GetTexture("Fighter"))
    end
--    local fighter = player:GetComponent(Component.SPRITE2D)
--    print(fighter)
--    fighter:SetSprite(self.RManager:GetTexture("Fighter"))
    -- player:AddComponent(fighterCollider)
    player:SetPosition(200,200)
end

function Player:OnKeyPressed(event)
    self.i = self.i + 1
    self:Move(0,-1) 

    print(self.i)
    if sf.KeyEvent.GetKeyEventCode(event.key) == sf.KEY_Z then
        self:Move(0,-1) 
    end

--    if sf.KeyEvent.GetKeyEventCode(event.key) == sf.KEY_S then
--       self:Move(0,1) 
--    end

--    if sf.KeyEvent.GetKeyEventCode(event.key) == sf.KEY_Q then
--       self:Move(-1,0) 
--    end
--    if sf.KeyEvent.GetKeyEventCode(event.key) == sf.KEY_D then
--       self:Move(1,0) 
--    end
end

function Player:Move(x, y)
    local player = self.EManager:GetEntity(self.entityName)
    player:Move(x,y)
end

function Player:RegisterEvents()
    self.EventManager:RegisterEvent(Input.INPUT_EVENT_KEY_PRESSED, function(event) self:OnKeyPressed(event) end)
end

function Player:Test()
    for i = 1, 300 do
        self:Move(0,1)
    end
end


-- Create the player and register events
Player:Create()
--Player:Test()
Player:RegisterEvents()
