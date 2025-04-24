#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <queue>
#include <algorithm>

using namespace std;

class Twitter {
private:
    int timestamp = 0;  // Variable para simular el tiempo de los tweets
    unordered_map<int, deque<pair<int, int>>> userTweets; // Mapa para almacenar tweets de cada usuario
    unordered_map<int, unordered_set<int>> following;     // Mapa para almacenar los usuarios que sigue cada usuario

public:
    Twitter() {}  // Constructor vacío que inicializa la clase

    // Método para publicar un tweet
    void postTweet(int userId, int tweetId) {
        timestamp++;  // Incrementa el tiempo para el nuevo tweet
        userTweets[userId].emplace_front(timestamp, tweetId);  // Añade el tweet al principio del deque del usuario

        // Si el usuario tiene más de 10 tweets, eliminamos el más antiguo
        if (userTweets[userId].size() > 10) {
            userTweets[userId].pop_back();
        }
    }

    // Método para obtener el news feed de un usuario
    vector<int> getNewsFeed(int userId) {
        // Comparador para la cola de prioridad (min-heap) para mantener el orden de los tweets por timestamp
        auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.first > b.first;  // Ordena por el timestamp (de más reciente a más antiguo)
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> minHeap(cmp);  // Cola de prioridad

        unordered_set<int> users = following[userId];  // Obtiene los usuarios que sigue
        users.insert(userId);  // Añade el propio usuario al conjunto para incluir sus propios tweets

        // Recorre los usuarios seguidos y sus tweets
        for (int uid : users) {
            for (const auto& tweet : userTweets[uid]) {
                minHeap.push(tweet);  // Añade el tweet a la cola de prioridad

                // Si la cola tiene más de 10 tweets, elimina el más antiguo
                if (minHeap.size() > 10) {
                    minHeap.pop();
                }
            }
        }

        vector<int> result;
        // Extrae los tweets del min-heap (de los más recientes a los más antiguos)
        while (!minHeap.empty()) {
            result.push_back(minHeap.top().second);
            minHeap.pop();
        }
        reverse(result.begin(), result.end());  // Invertimos el orden para tener los tweets de más reciente a más antiguo
        return result;
    }

    // Método para seguir a otro usuario
    void follow(int followerId, int followeeId) {
        if (followerId != followeeId) {
            following[followerId].insert(followeeId);  // Añade a followeeId al conjunto de seguidos de followerId
        }
    }

    // Método para dejar de seguir a otro usuario
    void unfollow(int followerId, int followeeId) {
        following[followerId].erase(followeeId);  // Elimina a followeeId del conjunto de seguidos de followerId
    }
};
