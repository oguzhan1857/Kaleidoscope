kaleidoscope  = __import__("kaleidoscope")

class Spell:
    def __init__(self, slot_id):
        self.slot_index = slot_id
        self.player     = kaleidoscope.GetPlayer()
        self.instance   = self.player.GetSpellbook().GetSpellSlot(slot_id)
        self.data       = self.instance.GetSpellInfo().GetSpellData()

    def is_ready(self):
        return self.get_cd_remain() == 0.0

    def get_cd_remain(self):
        return max(self.instance.GetCooldownExpire() - kaleidoscope.GetTime(), 0.0)

    def get_cooldown(self):
        return self.instance.GetCooldown()

    def is_learned(self):
        return self.instance.GetLevel() > 0

    def get_mana_cost(self):
        return self.data.GetManaCost()

    def get_player_mana_percent(self):
        return self.player.GetMana() / self.player.GetMaxMana() * 100

    def can_use(self):
        if self.is_learned() and self.is_ready():
            return True
        return False