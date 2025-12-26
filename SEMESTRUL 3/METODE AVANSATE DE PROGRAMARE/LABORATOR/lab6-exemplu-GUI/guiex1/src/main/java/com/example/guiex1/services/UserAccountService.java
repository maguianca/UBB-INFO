package com.example.guiex1.services;

import com.example.guiex1.domain.*;
import com.example.guiex1.repository.dbrepo.UtilizatorDbRepository;
import com.example.guiex1.utils.events.ChangeEventType;
import com.example.guiex1.utils.events.UtilizatorEntityChangeEvent;
import com.example.guiex1.utils.observer.Observable;
import com.example.guiex1.utils.observer.Observer;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class UserAccountService implements Observable<UtilizatorEntityChangeEvent> {
    private UtilizatorDbRepository repo;
    private List<Observer<UtilizatorEntityChangeEvent>> observers = new ArrayList<>();

    private UserAccountService() {
        this.repo = createUserRepo();
    }

    private static UserAccountService instance;

    private UtilizatorDbRepository createUserRepo(){
        String username="postgres";
        String pasword="Iris";
        String url="jdbc:postgresql://localhost:5432/SocialNetwork";
        UtilizatorDbRepository utilizatorRepository =
                new UtilizatorDbRepository(url,username, pasword,  new UtilizatorValidator());
        return utilizatorRepository;
    }

    public static UserAccountService getInstance(){
        if(instance == null)
            instance = new UserAccountService();
        return instance;
    }

    @Override
    public void addObserver(Observer<UtilizatorEntityChangeEvent> e) {
        observers.add(e);

    }

    @Override
    public void removeObserver(Observer<UtilizatorEntityChangeEvent> e) {
        //observers.remove(e);
    }

    @Override
    public void notifyObservers(UtilizatorEntityChangeEvent t) {

        observers.stream().forEach(x -> x.update(t));
    }

    public Optional<Utilizator> findOne(Long id) {
        return repo.findOne(id);
    }

    public void removeFriendship(Long firstId, Long secondId) {
        repo.deleteFriendship(firstId, secondId);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.UPDATE, findOne(firstId).get()));
    }

    public Long findIdByName(String firstName, String lastName) {
        Optional<Utilizator> user = repo.findOne(firstName, lastName);
        return user.map(Entity::getId).orElse(null);
    }

    public List<UserWithDateDTO> allUsersWhoRequestedFriendship(Long id) {
        List<friendRequestDTO> idsWhoRequestedFriendship = repo.getFriendRequestWithDateForUserId(id);
        List<UserWithDateDTO> usersWhoRequestedFriendship = new ArrayList<>();
        for (friendRequestDTO friendRequestDto : idsWhoRequestedFriendship) {
            Optional<Utilizator> user = findOne(friendRequestDto.getUserWhoRequestsFriendshipId());
            if (user.isPresent()) {
                usersWhoRequestedFriendship.add(new UserWithDateDTO(user.get(), friendRequestDto.getRequestDate()));
            }
        }
        return usersWhoRequestedFriendship;
    }

    public void acceptFriendRequest(Long userId, Long userToAcceptFriendshipRequestId) {
        repo.deleteFriendRequest(userToAcceptFriendshipRequestId, userId);
        repo.addFriendship(userId, userToAcceptFriendshipRequestId, LocalDate.now());
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.UPDATE, findOne(userId).get()));
    }

    public void deleteFriendRequest(Long userToDeleteFriendshipId, Long userId) {
        repo.deleteFriendRequest(userToDeleteFriendshipId, userId);
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.UPDATE, findOne(userId).get()));
    }

    public List<Utilizator> usersWhoAreNotFriendsOrRequestedForAUserId(Long userID) {
        List<Long> allIDs = repo.getAllUserIds();
        List<Long> alreadyFriends = repo.getFriendsForUserId(userID);
        List<Long> alreadyRequested = repo.idsOfUsersIRequestedFriendshipFrom(userID);
        List<Long> toWhomIRequested = repo.getFriendRequestForUserId(userID);

        List<Utilizator> remainingUsers = new ArrayList<>();
        for (Long id : allIDs) {
            if (!((((alreadyFriends.contains(id) || alreadyRequested.contains(id)) || id == userID) || toWhomIRequested.contains(id)) )) {
                Optional<Utilizator> userToAdd = findOne(id);
                if (userToAdd.isPresent())
                    remainingUsers.add(userToAdd.get());
            }

        }
        return remainingUsers;

    }

    public void requestFriendship(Long idWhoRequests, Long toWhomIRequest) {
        repo.addFriendshipRequest(idWhoRequests,toWhomIRequest,LocalDate.now());
        notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.UPDATE,findOne(idWhoRequests).get()));
    }

    public Page<Utilizator> getFriendsForUserID(Long userID, Pageable pageable){

        Page<Long> page = repo.getPagedFriendsForUserID(userID,pageable);
        List<Utilizator> friendList = new ArrayList<>();

        for(Long friendID: page.getElementsOnPage()){
            Optional<Utilizator> user = findOne(friendID);
            user.ifPresent(friendList::add);
        }
        return new Page<>(page.getTotalNumberOfElements(),friendList);
    }
}