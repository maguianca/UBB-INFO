package com.example.guiex1.services;



import com.example.guiex1.domain.Friendship;
import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.repository.Repository;
import com.example.guiex1.utils.events.ChangeEventType;
import com.example.guiex1.utils.events.UtilizatorEntityChangeEvent;
import com.example.guiex1.utils.observer.Observable;
import com.example.guiex1.utils.observer.Observer;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class UtilizatorService implements Observable<UtilizatorEntityChangeEvent> {
    private Repository<Long, Utilizator> repo;
    private Repository<Long, Friendship> repoFriends;
    private List<Observer<UtilizatorEntityChangeEvent>> observers=new ArrayList<>();

    public UtilizatorService(Repository<Long, Utilizator> repo, Repository<Long, Friendship> repoFriends) {
        this.repoFriends = repoFriends;
        this.repo = repo;
    }

    public Long getNewUserId() {
        Long id =0L;
        for(Utilizator u:repo.findAll()){
            id=u.getId();
        }
        id++;
        return id;
    }
    public Utilizator addUtilizator(Utilizator user) {
        user.setId(getNewUserId());
        if(repo.save(user).isEmpty()){
            UtilizatorEntityChangeEvent event = new UtilizatorEntityChangeEvent(ChangeEventType.ADD, user);
            notifyObservers(event);
            return null;
        }
        return user;
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
            if (newUser.isEmpty())
                notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.UPDATE, u, oldUser.get()));
            return newUser.orElse(null);
        }
        return oldUser.orElse(null);
    }
    public Iterable<Friendship> getFriendships() {
        return repoFriends.findAll();
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
    public List<LocalDateTime> getDates(Long id){
        List<LocalDateTime> friends = new ArrayList<>();
        getFriendships().forEach(friendship -> {
            if (friendship.getIdUser1().equals(id)) {
                friends.add(friendship.getDate());
            }
            if (friendship.getIdUser2().equals(id)) {
                friends.add(friendship.getDate());
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
    public Optional<Utilizator> getUserById(Long id) {
        return repo.findOne(id); // Directly delegate to repository
    }

    public void deleteFriendship(Long id) {
        repoFriends.delete(id);
    }
}
