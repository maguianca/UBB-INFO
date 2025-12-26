package com.example.guiex1.services;
import com.example.guiex1.domain.Friendship;
import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.repository.Repository;
import com.example.guiex1.repository.dbrepo.PagingFriendship;
import com.example.guiex1.utils.events.ChangeEventType;
import com.example.guiex1.utils.events.UtilizatorEntityChangeEvent;
import com.example.guiex1.utils.observer.Observable;
import com.example.guiex1.utils.observer.Observer;
import com.example.guiex1.utils.paging.Page;
import com.example.guiex1.utils.paging.Pageable;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

import static java.lang.Math.max;

public class UtilizatorService implements Observable<UtilizatorEntityChangeEvent> {
    private Repository<Long, Utilizator> repo;
    private PagingFriendship<Long,Friendship> repoFriends;
    private Repository<Long, Friendship> repoRequest;
    private List<Observer<UtilizatorEntityChangeEvent>> observers=new ArrayList<>();

    public UtilizatorService(Repository<Long, Utilizator> repo, PagingFriendship<Long,Friendship>  repoFriends,Repository<Long, Friendship> repoRequest) {
        this.repoFriends = repoFriends;
        this.repo = repo;
        this.repoRequest = repoRequest;
    }
    public Optional<Utilizator> findbyName(String username) {
        return StreamSupport.stream(repo.findAll().spliterator(), false)
                .filter(user -> user.getUsername().equals(username))
                .findFirst();

    }
    public Long getNewUserId() {
        Long id =0L;
        for(Utilizator u:repo.findAll()){
            id=max(u.getId(),id);
        }
        id++;
        return id;
    }
    public Long getNewFriendshipId() {
        Long id =0L;
        for(Friendship u:repoFriends.findAll()){
            id=max(u.getId(),id);
        }
        id++;
        return id;
    }
    public Long getNewRequestId() {
        Long id = StreamSupport.stream(repoRequest.findAll().spliterator(), false)
                .map(Friendship::getId)
                .reduce(Long.MIN_VALUE, Long::max);
        return id + 1;
    }

    public Utilizator addUtilizator(Utilizator user) {
        user.setId(getNewUserId());
        if(repo.save(user).isPresent()){
            UtilizatorEntityChangeEvent event = new UtilizatorEntityChangeEvent(ChangeEventType.ADD, user);
            notifyObservers(event);
            return user;
        }
        return null;
    }
    public Utilizator findOne(Long id){
        return repo.findOne(id).orElse(null);
    }
    public Utilizator deleteUtilizator(Long id){
        Optional<Utilizator> user=repo.delete(id);
        if (user.isPresent()) {
            notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.DELETE, user.get()));
            return user.get();
        }
        return null;
    }

    public Iterable<Utilizator> getAll(){
        return repo.findAll();
    }
    public List<Utilizator> getRestUsers(Long id) {
        return StreamSupport.stream(repo.findAll().spliterator(), false)
                .filter(user -> user.getId() != id)
                .collect(Collectors.toList());
    }
    public void addFriendship(Long userId, Long friendId) {
        Optional<Utilizator> user = repo.findOne(userId);
        Optional<Utilizator> friend = repo.findOne(friendId);
        System.out.println("a");
        Optional<Long>already_friendship=getFrId(userId,friendId);
        if(already_friendship.isPresent()){
            throw new IllegalArgumentException("Friendship already exists");
        }
        if (user.isPresent() && friend.isPresent()) {
            Friendship friendship = new Friendship(userId, friendId, LocalDateTime.now());
            Long id=getNewFriendshipId();
            friendship.setId(id);
            repoFriends.save(friendship);
            notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.ADD, user.get()));
            System.out.println("aici");
        } else {
            throw new IllegalArgumentException("User or Friend does not exist.");
        }
    }
    public void addRequest(Long userId, Long friendId) {
        Optional<Utilizator> user = repo.findOne(userId);
        Optional<Utilizator> friend = repo.findOne(friendId);
        Optional<Long>already_friendship=getFrId(userId,friendId);
        Optional<Long>already_request=getRequestId(userId,friendId);
        if(already_friendship.isPresent()){
            throw new IllegalArgumentException("Friendship already exists");
        }
        if(already_request.isPresent()){
            throw new IllegalArgumentException("The request already exists");
        }
        if (user.isPresent() && friend.isPresent()) {
            Friendship request = new Friendship(userId, friendId, LocalDateTime.now());
            Long id=getNewRequestId();
            request.setId(id);
            repoRequest.save(request);
            notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.ADD, user.get()));
        } else {
            throw new IllegalArgumentException("User or Friend does not exist.");
        }
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

        observers.stream().forEach(x->x.update(t));
    }

    public Utilizator updateUtilizator(Utilizator u) {
        Optional<Utilizator> oldUser=repo.findOne(u.getId());
        if(oldUser.isPresent()) {
            Optional<Utilizator> newUser=repo.update(u);
            if (newUser.isPresent())
                notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.UPDATE, u, oldUser.get()));
            return newUser.orElse(null);
        }
        return oldUser.orElse(null);
    }
    public Iterable<Friendship> getFriendships() {
        return repoFriends.findAll();
    }
    public Iterable<Friendship> getRequests() {
        return repoRequest.findAll();
    }
    public List<Long> getFriends(Long id){
        List<Long> friends = new ArrayList<>();
        getFriendships().forEach(friendship -> {
            if (friendship.getIdUser1().equals(id)) {
                friends.add(friendship.getIdUser2());
            }
            if (friendship.getIdUser2().equals(id)) {
                friends.add(friendship.getIdUser1());
            }
        });
        return friends;
    }
    public List<Long> getRequests(Long id){
        List<Long> future_friends = new ArrayList<>();
        getRequests().forEach(friendship -> {
            /*if (friendship.getIdUser1().equals(id)) {
                future_friends.add(friendship.getIdUser2());
            }*/
            if (friendship.getIdUser2().equals(id)) {
                future_friends.add(friendship.getIdUser1());
            }
        });
        return future_friends;
    }
    public List<LocalDateTime> getDates(Long id){
        List<LocalDateTime> friends = new ArrayList<>();
        getFriendships().forEach(friendship -> {
            if (friendship.getIdUser1().equals(id)) {
                friends.add(friendship.getDate());
                System.out.println("id:"+ friendship.getIdUser2()+"date"+friendship.getDate());
            }
            if (friendship.getIdUser2().equals(id)) {
                friends.add(friendship.getDate());
                System.out.println("id:"+ friendship.getIdUser1()+"date"+friendship.getDate());
            }
        });
        return friends;
    }
    public List<LocalDateTime> getRequestDates(Long id){
        List<LocalDateTime> friends = new ArrayList<>();
        getRequests().forEach(friendship -> {
            if (friendship.getIdUser1().equals(id)) {
                friends.add(friendship.getDate());
                System.out.println("id:"+ friendship.getIdUser2()+"date"+friendship.getDate());
            }
            if (friendship.getIdUser2().equals(id)) {
                friends.add(friendship.getDate());
                System.out.println("id:"+ friendship.getIdUser1()+"date"+friendship.getDate());
            }
        });
        return friends;
    }
    public Optional<Long> getFrId(Long id1, Long id2) {
        for (Friendship friendship : getFriendships()) {
            if ((friendship.getIdUser1().equals(id1) && friendship.getIdUser2().equals(id2)) ||
                    (friendship.getIdUser1().equals(id2) && friendship.getIdUser2().equals(id1))) {
                return Optional.of(friendship.getId());
            }
        }
        return Optional.empty();
    }
    public Optional<Long> getRequestId(Long id1, Long id2) {
        for (Friendship friendship : getRequests()) {
            if ((friendship.getIdUser1().equals(id1) && friendship.getIdUser2().equals(id2)) ||
                    (friendship.getIdUser1().equals(id2) && friendship.getIdUser2().equals(id1))) {
                return Optional.of(friendship.getId());
            }
        }
        return Optional.empty();
    }
    public Optional<Utilizator> getUserById(Long id) {
        return repo.findOne(id);
    }

    public Optional<Friendship> deleteFriendship(Long id) {
        return repoFriends.delete(id);
    }
    public Optional<Friendship> deleteRequest(Long id) {
        return repoRequest.delete(id);

    }
    public Page<Utilizator> getFriendsForUserID(Long userID, Pageable pageable){

        Page<Long> page = repoFriends.getPagedFriendsForUserID(userID,pageable);
        List<Utilizator> friendList = new ArrayList<>();

        for(Long friendID: page.getElementsOnPage()){
            Optional<Utilizator> user = repo.findOne(friendID);
            user.ifPresent(friendList::add);
        }
        return new Page<>(page.getTotalNumberElements(),friendList);
    }

    public int getNumberMutualFriends(Long id, Long id1) {
        AtomicInteger count = new AtomicInteger();
        List<Long> friendsOfId1 = getFriends(id1);
        getFriends(id).forEach(friend -> {
            if (friendsOfId1.contains(friend)) {
                count.getAndIncrement();
            }
        });
        return count.get();
    }
    public void update(Utilizator u){
        repo.update(u);
    }
}
