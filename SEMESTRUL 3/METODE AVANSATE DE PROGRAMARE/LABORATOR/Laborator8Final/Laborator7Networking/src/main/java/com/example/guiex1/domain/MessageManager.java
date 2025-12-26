package com.example.guiex1.domain;

import javafx.util.Pair;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class MessageManager {
    private Map<Long, List<Pair<Utilizator, Boolean>>> friendRequests = new HashMap<>(); // User ID -> List of requests

    public void addFriendRequest(Utilizator sender, Utilizator receiver) {
        List<Pair<Utilizator, Boolean>> requests = friendRequests.computeIfAbsent(receiver.getId(), k -> new ArrayList<>());
        requests.add(new Pair<>(sender, false)); // Marked as not seen
    }

    public List<Pair<Utilizator, Boolean>> getNewFriendRequests(Utilizator user) {
        return friendRequests.getOrDefault(user.getId(), new ArrayList<>())
                .stream()
                .filter(request -> !request.getValue()) // Only unseen requests
                .collect(Collectors.toList());
    }

    public void markRequestsAsSeen(Utilizator user) {
        List<Pair<Utilizator, Boolean>> requests = friendRequests.get(user.getId());
        if (requests != null) {
            requests.forEach(request -> request = new Pair<>(request.getKey(), true)); // Mark as seen
        }
    }
}
