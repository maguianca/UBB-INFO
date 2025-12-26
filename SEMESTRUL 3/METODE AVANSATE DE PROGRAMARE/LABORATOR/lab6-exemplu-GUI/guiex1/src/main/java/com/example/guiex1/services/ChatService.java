package com.example.guiex1.services;

import com.example.guiex1.domain.ChatUserDTO;
import com.example.guiex1.domain.Message;
import com.example.guiex1.domain.Utilizator;
import com.example.guiex1.domain.UtilizatorValidator;
import com.example.guiex1.repository.dbrepo.UtilizatorDbRepository;
import com.example.guiex1.utils.events.ChangeEventType;
import com.example.guiex1.utils.events.UtilizatorEntityChangeEvent;
import com.example.guiex1.utils.observer.Observable;
import com.example.guiex1.utils.observer.Observer;

import java.time.LocalDateTime;
import java.util.*;

public class ChatService implements Observable<UtilizatorEntityChangeEvent> {
    UtilizatorDbRepository repo;
    private static ChatService instance;
    private List<Observer<UtilizatorEntityChangeEvent>> observers = new ArrayList<>();

    private ChatService(){
        this.repo = createUserRepo();
    }
    public static ChatService getInstance(){
        if(instance == null)
            instance = new ChatService();
        return instance;
    }

    private UtilizatorDbRepository createUserRepo(){
        String username="postgres";
        String pasword="Iris";
        String url="jdbc:postgresql://localhost:5432/SocialNetwork";
        UtilizatorDbRepository utilizatorRepository =
                new UtilizatorDbRepository(url,username, pasword,  new UtilizatorValidator());
        return utilizatorRepository;
    }

    public List<ChatUserDTO> getChatOptions(Long userID){
        return repo.getFriendsForUserId(userID).stream()
                .map(repo::findOne)
                .filter(Optional::isPresent)
                .map(Optional::get)
                .map(user -> new ChatUserDTO(user.getFirstName(),user.getLastName()))
                .toList();
//  List<Long> chatOptionList = repo.getFriendsForUserId(userID);
//        List<ChatUserDTO> chatOptions = new ArrayList<>();
//
//        for(Long id: chatOptionList){
//            Optional<Utilizator> chatOption = repo.findOne(id);
//            chatOption.ifPresent(x->chatOptions.add(new ChatUserDTO(x.getFirstName(),x.getLastName())));
//        }
//        return chatOptions;
    }
    public Long findIdByName(String firstName, String lastName){
        return repo.findOne(firstName,lastName)
                .map(Utilizator::getId)
                .orElseThrow(() -> new RuntimeException("user not found"));
//        Optional<Utilizator> user = repo.findOne(firstName,lastName);
//        if(user.isPresent()){
//            return user.get().getId();
//        }
//        throw new RuntimeException("...");
    }

    public List<Message> getMessagesSorted(Long firstId, Long secondId) {
        return repo.getMessages(firstId,secondId).stream()
                .sorted(Comparator.comparing(Message::getSendDate))
                .toList();
//        List<Message> messageList = repo.getMessages(firstId,secondId);
//        messageList.sort(Comparator.comparing(Message::getSendDate));
//        return messageList;
    }

    public void addMessageFrom(Long senderID, Long receiverID, String messageContent) {
        Optional<Utilizator> sender = repo.findOne(senderID);
        Optional<Utilizator> receiver = repo.findOne(receiverID);
        if(sender.isPresent() && receiver.isPresent()) {
            Message messageToSave = new Message(sender.get(), receiver.get(), messageContent, LocalDateTime.now(), null);
            repo.addMessage(messageToSave);
            notifyObservers(new UtilizatorEntityChangeEvent(ChangeEventType.UPDATE,sender.get()));
        }
        else
            throw new RuntimeException("One of the users in the chat does not exist...");
    }

    @Override
    public void addObserver(Observer<UtilizatorEntityChangeEvent> e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer<UtilizatorEntityChangeEvent> e) {
        observers.remove(e);
    }

    @Override
    public void notifyObservers(UtilizatorEntityChangeEvent t) {
        observers.stream().forEach(x -> x.update(t));
    }
}
