MONSTER_LEVELS = {
  1 => { hp: 4, damage: 1, weapons: ["P", "F", "C", "O"] },
  2 => { hp: 6, damage: 1, weapons: ["P", "F", "C"] },
  3 => { hp: 4, damage: 2, weapons: ["P", "F", "C", "O", "#"] },
}

def load_monsters
  File.readlines("monsters.txt").map do |line|
    monster_attrs = line.split(";")
    id = monster_attrs[0].to_i
    level = monster_attrs[1].to_i
    name = monster_attrs[2].strip
    {
      id: id,
      name: name,
      hp: MONSTER_LEVELS[level][:hp],
      damage: MONSTER_LEVELS[level][:damage],
      weapons: MONSTER_LEVELS[level][:weapons],
    }
  end
end

def find_monsters_by_ids(ids)
  ids.map do |id|
    m = @monsters.find { |monster| monster[:id] == id.to_i }
    if m.nil?
      puts "Monstre inconnu : #{id}"
    end
    m
  end
end

def load_stage(stage)
  phases = File.readlines("stages/#{stage}.txt").map do |phase|
    phase_attrs = phase.split(";")
    context = phase_attrs[0]
    monsters_ids = phase_attrs - [phase_attrs[0]]
    {
      context: context,
      monsters: find_monsters_by_ids(monsters_ids)
    }
  end

  for phase in phases
    run_phase(phase)
  end
end

def run_phase(phase)
  return if !knight_alive?

  puts "Contexte :"
  puts phase[:context]

  for monster in phase[:monsters]
    fight_monster(monster)
  end
end

def fight_monster(monster)
  return if !knight_alive?

  puts "Le monstre #{monster[:name]} (#{monster[:hp]} HP, #{monster[:damage]} damage) accoure et se prépare à t'attaquer !"
  while (@knight[:hp] > 0 && monster[:hp] > 0) do
    puts "Choisis ton arme parmi P,F,C"
    attack_monster(monster)
  end

  if monster[:hp] <= 0
    puts "Le monstre #{monster[:name]} est mort"
  else
    puts "#{@knight[:name]} succombe aux coups de #{monster[:name]}. Quelle triste fin pour le monde !"
  end
end

def knight_alive?
  @knight[:hp] > 0
end

def attack_monster(monster)
  knight_name = @knight[:name]
  knight_weapon = test? ? "P" : input
  monster_weapon = monster[:weapons].sample
  monster_name = monster[:name]
  puts "#{knight_name}(#{knight_weapon}) attaque #{monster[:name]}(#{monster_weapon})"
  fight_outcome = knight_wins?(knight_weapon, monster_weapon)
  case fight_outcome
  when 0
    puts "Egalité"
  when 1
    monster[:hp] = monster[:hp] - 1
    puts "#{knight_name}(#{@knight[:hp]} HP) gagne l'attaque contre #{monster_name}( #{monster[:hp]} HP)"
  when -1
    @knight[:hp] = @knight[:hp] - monster[:damage]
    @knight[:hp] = 0 if @knight[:hp] < 0
    puts "#{knight_name}(#{@knight[:hp]} HP) perd l'attaque contre #{monster_name}( #{monster[:hp]} HP)"
  end
end

#  0: égalité
#  1: knight wins
# -1: monster wins
def knight_wins?(knight_weapon, monster_weapon)
  if knight_weapon == monster_weapon
    return 0
  end

  case monster_weapon
  when "P"
    if knight_weapon == "F"
      return 1
    else
      return -1
    end
  when "C"
    if knight_weapon == "P"
      return 1
    else
      return -1
    end
  when "F"
    if knight_weapon == "C"
      return 1
    else
      return -1
    end
  when "O"
    return 1
  when "#"
    return -1
  else
    puts "Erreur : arme inconnue #{monster_weapon}"
  end
end

def start_stage
  puts "Nom de la partie :"
  stage_name = test? ? "stage1" : input
  puts "Nom du joueur :"
  @knight[:name] = test? ? "Toto" : input
  @knight[:hp] = 20
  load_stage(stage_name)
end

def show_menu
  puts "
end
  ------------- Menu -------------
  1. jouer une partie prédéfinie
  2. créer une nouvelle partie
  3. afficher la liste des joueurs triée par nom
  4. afficher la liste des joueurs triée par meilleur score
  5. afficher les statistiques d'un joueur
9. Quitter
--------------------------------"
end

def input
  gets.chomp
end

def test?
  ENV["TEST"] != nil
end

def main
  @monsters = load_monsters
  @knight = {
    name: nil,
    hp: 20,
  }

  while (true) do
    show_menu
    choice = input

    case choice
    when "1"
      start_stage
    when "2"
    when "3"
    when "4"
    when "5"
    when "9"
      exit(0)
    else
      puts "choix invalide"
    end
  end
end

main