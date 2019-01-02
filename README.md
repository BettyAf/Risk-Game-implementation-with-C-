## Part1 
<ul> <li> Problem statement
  <ul>
  <li> Map
  
It implements a map for the game of Risk. The map class implemented as a connected graph, where each node represents a country. Edges between nodes represent adjacency between countries. Each country can have any number of adjacent countries. Continents must also be connected subgraphs, where each country belongs to one and only one continent. Each country is owned by a player and contain a number of armies. The map class can be used to represent any map configuration (i.e. not only the “Risk” map). It delivers a driver that creates a map and demonstrates that the map class implements the following verifications: 1) the map is a connected graph, 2) continents are connected subgraphs and 3) each country belongs to one and only one continent. The driver provides test cases for various valid/invalid maps.
  </li>
  <li> Map loader
 
 A group of C++ classes that reads and loads a map file in the .map text file format as found in the “Conquest Maps” resource, available at: http://www.windowsgames.co.uk/conquest_maps.html, for example the classic Risk map can be downloaded at http://www.windowsgames.co.uk/ConquestMaps/World.zip. The map loader is able to read any such map. The map loader stores the map as a graph data structure. The map loader is able to read any text file (even ones that do not constitute a valid map). It delivers a driver that reads various files and successfully creates a map object for valid map files, and rejects invalid map files.
  <li> Dice
  
A group of C++ classes that implements a dice rolling facility to be used during the attack phase. The dice rolling facility enables the player object to decide how many 6-sided dice are being rolled (from 1 to 3 dice), and then return the values in a container. Each player will have his own dice rolling object, and each dice rolling object must keep track of the percentage of each value that has been rolled up to now for this player in the game. It delivers a driver that creates at least 2 dice rolling facility objects, tests that 1) one can request from 1 to 3 dice being rolled, 2) that the container returns the right number of values, 3) that no value outside of the 1-6 range is ever returned, 4) that there is an equal share of 1-6 values returned and 5) that every dice rolling facility object maintains a percentage of all individual values rolled up to now.
  <li> Player
  
A group of C++ classes that implement a Risk player using the following design: A player owns a collection of countries (see Part 1). A player owns a hand of Risk cards (see Part 5). A player has his own dice rolling facility object (see Part 3). A player must implement the following methods, which are eventually going to get called by the game driver: reinforce(), attack(), fortify(). 
  <li> Cards deck/hand
  
A group of C++ classes that implements a deck and hand of Risk cards. The deck object is composed of as many cards as there are countries in the map. Each card has a type from: infantry, artillery, cavalry. The deck must have a draw() method that allows a player to draw a card at random from the cards remaining in the deck and place it in his hand of cards. The hand object is a collection of cards that has an exchange() method that allows the player to exchange cards in return for a certain number of armies (see the game rules for details).It demonstrates that it is composed of an equal share of infantry, artillery and cavalry cards by drawing all the cards and counting each sort drawn. It creates a hand object that is filled by drawing cards from the deck, and that return the right number of armies when the exchange() method is called, depending on what cards are in the hand.
</ul>

## Part2
<li> Problem statement
  <ul>
  <li> Game start
  
A group of C++ classes that implement a user interaction mechanism to start the game by allowing the player to 1) select a map from a list of map files as stored in a directory 2) select the number of players in the game (2-6 players). The code should then use the map loader to load the selected map, create all the players, assign dice rolling facilities to the players, create a deck of cards, and assign an empty hand of cards to each player. It has a driver that demonstrates that 1) different valid maps can be loaded and their validity is verified (i.e. it is a connected graph, etc), and invalid maps are rejected without the program crashing; 2) the right number of players is created, a deck with the right number of cards is created.
  <li> Game play: startup phase
  
A group of C++ classes that implements the startup phase following the official rules of the game of Risk. This phase is composed of the following sequence:
1. The order of play of the players in the game is determined randomly.
2. All countries in the map are randomly assigned to players one by one in a round-robin fashion.
3. Players are given a number of armies (A), to be placed one by one in a round-robin fashion on some of the countries that they own, where A is:
    <ul>
    <li> If 2 players, A=40
    <li> If 3 players, A=35
    <li> If 4 players, A=30
    <li> If 5 players, A=25
    <li> If 6 players, A=20
      </ul>
    
It delivers a driver that demonstrates that 1) all countries in the map have been assigned to one and only one player; 2) all players have eventually placed the right number of armies on their own countries after army placement is over.

<li> Game play: main game loop
  
Implements the main game loop following the official rules of the game of Risk. During the main game loop, proceeding in a round-robin fashion as setup in the startup phase, every player is given the opportunity to do each of the following actions during their turn:
1. Reinforcements phase
2. Attack phase
3. Fortification phase
This loop shall continue until only one player controls all the countries in the map, at which point a winner is announced and the game ends. You must deliver a driver that demonstrates that 1) every player gets turns in a round-robin fashion and that their reinforcement(), attack() and fortification() methods are called 2) the game ends when a player controls all the countries (the driver should explicitly give all the countries to one player, i.e. no real code for battles needs to be executed).
<li> Main game loop: reinforcement phase
Implements the reinforcement phase following the official rules of the game of Risk. In the reinforcement phase, the player gets a number of armies (A) to place on its countries, where A is:
  <ul>
    <li> Number of countries owned on the map, divided by 3 (rounded down), with a minimum of 3.
    <li> Continent-control value of all continents totally controlled by that player.
    <li> Armies resulting in card exchange, if possible. If a player owns more than 5 cards, it must exchange cards (exchanging cards should be done inside the Hand’s exchange() method).
  </ul>
The player then place all these armies on some of the countries it owns, as it sees fit (for now, it does not matter which). It delivers a driver that demonstrates that 1) a player receives the right number of armies in the reinforcement phase (showing different cases); 2) the player has effectively placed this exact number of new armies somewhere on the map by the end of the reinforcement phase.
<li> Main game loop: attack phase
  
Implements the attack phase following the official rules of the game of Risk. In this phase, the player is allowed to declare a series of attacks to try to gain control of additional countries, and eventually control the entire map. The attack phase follows the following loop:
  <ul>
    <li> The player decides if it will attack or not. If not, the attack phase is over.
    <li> The player selects one of its countries to attack from, and one of the neighbors of this country to attack (i.e. the attacked country belongs to another player). The attacking country must have at least 2 armies on it.
    <li> The attacker and defender players choose the number of dice to roll for their attack/defense. The attacker is allowed 1 to 3 dice, with the maximum number of dice being the number of armies on the attacking country, minus one. The defender is allowed 1 to 2 dice, with the maximum number of dice being the number of armies on the defending country.
    <li> The dice are rolled for each player and sorted, then compared pair-wise. For each pair, the player with the lowest roll loses one army. If the pair is equal, the attacker loses an army.
    <li> If the attacked country runs out of armies, it has been defeated. The defending country now belongs to the attacking player. The attacker is allowed to move a number of armies from the attacking country to the attacked country, in the range [1 to (number of armies on attacking country -1)].
    <li> The player is allowed to initiate any number of attacks per turn, including 0.
  </ul>
It delivers a driver that demonstrates that 1) only valid attacks can be declared (i.e. valid attacker/attacked country); 2) only valid number of dice can be chosen by the attacker/defender; 3) given known dice values, that the right number of armies are deducted on the attacker/defender; 4) the attacker is allowed to initiate multiple attacks, until it declares that it does not want to attack anymore.
<li> Main game loop: fortification phase
  
Implements the fortification phase following the official rules of the game of Risk. In the fortification phase, the player is allowed to move a number of armies (X) from one of its countries (the source country) to one of its neighbors that it also owns (the target country). X must be in the range [1 to (number of armies on the source country - 1)]. It delivers a driver that demonstrates that 1) only valid countries can be selected as source/target; 2) only a valid number of armies can be moved; 3) the right number of armies is effectively moved.
  </ul>
  
  ## Part3
  <li> Problem statement
  <ul>
    <li> Player Strategy Pattern
      
Using the Strategy design pattern, implementing different kinds of players that make different decisions during the
reinforcement, attack, and fortification phases. The kinds of players are: (1) human player that requires user
interaction to make decisions, (2) an aggressive computer player that focuses on attack (reinforces its strongest
country, then always attack with it until it cannot attack anymore, then fortifies in order to maximize aggregation of
forces in one country), (3) a benevolent computer player that focuses on protecting its weak countries (reinforces
its weakest countries, never attacks, then fortifies in order to move armies to weaker countries).
    <li> Phase Observer
  
Using the Observer design pattern, implement a view that displays information happening in the current phase. It
should first display a header showing what player and what phase is currently being played, e.g. “Player 3: Attack
phase” or “Player 1: Fortification phase” Then it should display important information related to what is happening
in this phase, which should be different depending on what phase is being played. This should dynamically be
updated as the game goes through different players/phases and be visible at all times during game play.
    <li> Game Statistics Observer
  
Using the Observer design pattern, implement a view that displays some useful statistics about the game, the
minimum being a “players world domination view” that shows using some kind of bar graph depicting what
percentage of the world is currently being controlled by each player. This should dynamically be updated as the
map state changes and be visible at all times during game play.
  </ul>
  
  ## Part4
   <li> Problem statement
   <ul>
    <li> Game Statistics Observer Decorator
      
Using the Observer design pattern, implement a view that displays some useful statistics about the game as it is being played. This dynamically is updated as various aspect of the game state changes and be visible at all times during game play. Using the Decorator pattern, provide different decorators that add more information to be displayed on the Basic (undecorated) Game Statistics Observer:
1. Basic (undecorated) Game Statistics Observer: Display the turn number, update the view every time a new turn starts.
2. Player Domination Observer Decorator: Display the percentage of countries owned by each player, update the view when any player conquers a country.
3. Player Hands Observer Decorator: Display the cards owned by every player, update the view when any player’s hand is changing.
4. Continent Control Observer Decorator: Display what player controls each continent, update the view when any continent becomes controlled by a player, or when a player loses control of a continent.
IT demonstrateS that the Basic (undecorated) Game Statistics Observer is available at all times during play and updates the view when the turn number increases. Before the beginning of every turn, the user should be given the opportunity to add one or more Decorators (2, 3, or 4) above, which should result in the Observer to show more information and be notified as instructed above for each Decorator. Each Decorator (2,3,4) should not be used more than once. The user should also be allowed to remove Decorators. The user should be allowed to specify that it does not want to add/remove Decorators in the future, after which the user shall not be prompted anymore at the beginning of every turn.
      <li> New Strategies
  
 Add 2 more computer strategies (you should then have a total of 4 different computer strategies). These strategies is designed so that they have a chance to win the game (e.g. the “benevolent” strategy in Part 3 cannot win a game).
        <ul>
          <li> A Random Computer Player Strategy that reinforces random a random country, attacks a random number of times a random country, and fortifies a random country, all following the standard rules for each phase,
          <li> A Cheater Computer Player Strategy whose reinforce() method doubles the number of armies on all its countries, whose attack() method automatically conquers all the neighbors of all its countries, and whose fortify() method doubles the number of armies on its countries that have neighbors that belong to other players.
        </ul>
<li> Tournament
  
A tournament starts with the user choosing M = 1 to 5 different maps, P = 2 to 4 different computer players strategies, G = 1 to 5 games to be played on each map, D = 10 to 50 maximum number of turns for each game. A tournament is then automatically played by playing G games on each of the M different maps between the chosen computer player strategies. In order to minimize run completion time, each game is declared a draw after D turns. Once started, the tournament plays all the games automatically without user interaction. At the end of the tournament, a report of the results should be displayed, e.g.
M: Map1, Map2, Map3
P: Aggressive, Benevolent, Random, Cheater.
G: 4
D: 30
  </ul>
  </ul>
  
