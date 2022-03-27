kaleidoscope  = __import__("kaleidoscope")

class Damage:
    @staticmethod
    def calculate_auto_attack_damage(source, target):
        raw_physical_damage = source.GetBaseAttackDamage() + source.GetBonusAttackDamage()
        return Damage.calculate_physical_damage(source, target, raw_physical_damage)

    @staticmethod
    def calculate_physical_damage(source, target, damage):
        flat_armor_pen    = source.GetLethality() * (0.6 + (0.4 * source.GetLevel() / 18))
        percent_armor_pen = source.GetArmorPenPercent()

        base_armor  = target.GetArmor() - target.GetBonusArmor()
        bonus_armor = target.GetBonusArmor()

        base_armor  *= percent_armor_pen
        bonus_armor *= percent_armor_pen

        total_armor = base_armor + bonus_armor - flat_armor_pen

        if(total_armor >= 0):
            damage *= 100 / (100 + total_armor)
        else:
            damage *= 2 - (100 / (100 - total_armor))

        #item-rune-spell-summoner modifier
        
        return damage