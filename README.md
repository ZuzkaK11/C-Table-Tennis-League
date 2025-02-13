# C++-Table-Tennis-League

The Liga project is a C++ application designed to manage a league system. It includes functionality for handling players, matches, and league operations. The system allows adding players, planning and recording match results, and analyzing league statistics.

## Classes

### `Player`
Represents a player in the league.

- **Attributes:**
  - `std::string name` - The player's name.
  - `int points` - The player's total points.
  - `int matches` - The number of matches played.

- **Methods:**
  - `bool putPlayer(const std::string &Name)`  
    Validates and sets the player's name. Returns `true` if successful.
  - `int getPoints() const`  
    Returns the player's points.
  - `int getMatches() const`  
    Returns the number of matches played.
  - `std::string getName() const`  
    Returns the player's name.
  - `float getRatio() const`  
    Returns the win ratio (wins/total matches).
  - `void update(int result)`  
    Updates the player's points and matches based on the result.
  - `bool operator < (const Player &p) const`  
    Compares players by points.
  - `void reset()`  
    Resets the player's points and matches to 0.

---

### `Match`
Represents a single match between two players.

- **Attributes:**
  - `std::string player1` - Name of the first player.
  - `std::string player2` - Name of the second player.
  - `std::string result` - Match result in the format "x:y".
  - `Status status` - Match status (e.g., EXPECTED, DONE, DISQ).

- **Methods:**
  - `bool putMatch(const std::string &player1, const std::string &player2)`  
    Validates and sets player names. Initializes the match.
  - `bool putResult(const std::string &score)`  
    Validates and records the match result.
  - `std::string getResult()`  
    Returns the result of the match.
  - `std::string getResult_reverse()`  
    Returns the result in reversed player order.
  - `std::string getWinner()`  
    Returns the winner's name.
  - `void resetResult()`  
    Resets the match result to "0:0" and sets status to EXPECTED.

---

### `ListPlayers`
Manages a list of players.

- **Attributes:**
  - `std::vector<Player> listOfPlayers` - A list of all players.

- **Methods:**
  - `std::vector<Player> getPlayers()`  
    Returns the list of players.
  - `std::string add_player(const std::string &name)`  
    Adds a player to the list. Returns appropriate messages for success or errors.
  - `bool is_player_in(const std::string &name)`  
    Checks if a player exists in the list.
  - `Player* get_player(const std::string &name)`  
    Returns a pointer to a player or creates a new one if it doesn't exist.
  - `bool delete_player(const std::string &name)`  
    Deletes a player if they exist.
  - `void deleteAll_players()`  
    Clears the player list.

---

### `ListMatches`
Manages a list of matches.

- **Attributes:**
  - `std::vector<Match> listOfMatches` - A list of all matches.

- **Methods:**
  - `std::vector<Match> getMatches()`  
    Returns the list of matches.
  - `bool add_match(const std::string &player1, const std::string &player2)`  
    Adds a match between two players.
  - `bool delete_match(const std::string &match)`  
    Deletes a specific match.
  - `void delete_all_matches()`  
    Clears all matches from the list.

---

### `League`
Manages the league as a whole.

- **Attributes:**
  - `ListPlayers players` - List of players in the league.
  - `ListMatches matches` - List of matches in the league.

- **Methods:**
  - `std::string planMatch(const std::string &match)`  
    Plans a new match. Validates player names and match existence.
  - `std::string putResult(const std::string &match_result)`  
    Records the result of a planned match.
  - `bool changeResult(Match* &m, const std::string &score)`  
    Changes the result of a match.
  - `bool deletePlayer(const std::string &name)`  
    Removes a player and all associated matches.
  - `void simulateAllMatches()`  
    Simulates all possible matches in the league.
  - `void display_results(const std::string &name)`  
    Displays matches for a specific player or all matches.

---

## File Operations

- **Reading:**
  - `int readPlayers(const std::string &file)`  
    Reads player names from a file.
  - `bool readMatches(const std::string &file)`  
    Reads match results or plans matches from a file.

- **Writing:**
  - `bool writeResults(const std::string &file)`  
    Writes all matches to a file.
  - `bool writeTotalResults(const std::string &file)`  
    Writes player statistics and match results to a file.

---

## Simulation and Comparison

- `bool simulateNextMatches(const int &number)`  
  Simulates the next specified number of matches.
- `std::vector<Player> getOrderedPlayers(const int &method)`  
  Returns a sorted list of players based on the given method (e.g., SCORE, RATIO).

---

## Enums

- **Player Result Status:**
  - `WIN`, `LOST`, `RESET_WIN`, `RESET_LOST`.

- **Match Status:**
  - `DONE`, `EXPECTED`, `DISQ`.

- **Comparison Status:**
  - `SCORE`, `RATIO`, `MATCHES`, `NAME`.

