local Player = {
    entityName = "Player",
    i = 0,
    EManager = EntityManager:GetInstance(),
    RManager = ResourceManager:GetInstance(),
    EventManager = EventManager:GetInstance(),
}

function Player:Create()
    local player = self.EManager:CreateEntity(self.entityName)
    local playerEffect = self.EManager:CreateEntity("playerEffect")
    
    player:AddComponent(Component.SPRITE2D)
    player:AddComponent(Component.BOX_COLLIDER)
    playerEffect:AddComponent(Component.ANIMATION)

    local fighter = player:GetComponent(Component.SPRITE2D)
    local boxCollider = player:GetComponent(Component.BOX_COLLIDER)
    local fighterEffect = playerEffect:GetComponent(Component.ANIMATION)

        
    if fighter then
        fighter:SetSprite(self.RManager:GetTexture("Fighter"))
    end

    if boxCollider then
        boxCollider:SetSize(Vector2f(64,64))
    end

    if fighterEffect then
        fighterEffect:PlayAnimation("FighterEffectAnimation", true)
    end
        
    player:SetPosition(200,200)
    playerEffect:SetPosition(200,200)
end

function Player:OnKeyPressed(event)
--    self.i = self.i + 1
--    print(self.i)
    
    if sf.KeyEvent.GetKeyEventCode(event.key) == sf.KEY_Z then
        self:Move(0,-1) 
        self.EManager:GetEntity("playerEffect"):Move(0, -1)
    end

    if sf.KeyEvent.GetKeyEventCode(event.key) == sf.KEY_S then
       self:Move(0,1) 
       self.EManager:GetEntity("playerEffect"):Move(0, 1)
    end

    if sf.KeyEvent.GetKeyEventCode(event.key) == sf.KEY_Q then
       self:Move(-1,0)
       self.EManager:GetEntity("playerEffect"):Move(-1, 0)
    end
    
    if sf.KeyEvent.GetKeyEventCode(event.key) == sf.KEY_D then
       self:Move(1,0)
       self.EManager:GetEntity("playerEffect"):Move(1, 0)
    end
end

function Player:Move(x, y)
    local player = self.EManager:GetEntity(self.entityName)
    player:Move(x,y)
end

function Player:RegisterEvents()
    self.EventManager:RegisterEvent(Input.INPUT_EVENT_KEY_PRESSED, function(event) self:OnKeyPressed(event) end)
end


-- Create the player and register events
Player:Create()
Player:RegisterEvents()
