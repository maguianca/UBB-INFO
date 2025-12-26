package com.example.guiex1.services;

import com.example.guiex1.domain.*;
import com.example.guiex1.repository.Repository;
import com.example.guiex1.utils.events.MessageEntityChangeEvent;
import com.example.guiex1.utils.events.ChangeEventType;
import com.example.guiex1.utils.observer.Observable;
import com.example.guiex1.utils.observer.Observer;

import java.time.LocalDateTime;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class MessageService implements Observable<MessageEntityChangeEvent> {
    private final Repository<Long, Message> messageRepo;
    private final UtilizatorService utilizatorService;
    private final Repository<Tuple<Long, Long>, ReplyMessage> replyRepo;
    private List<Observer<MessageEntityChangeEvent>> observers = new ArrayList<>();

    public MessageService(UtilizatorService utilizatorService, Repository<Long, Message> messageRepo, Repository<Tuple<Long, Long>, ReplyMessage> replyRepo) {
        this.messageRepo = messageRepo;
        this.utilizatorService = utilizatorService;
        this.replyRepo = replyRepo;
    }

    @Override
    public void addObserver(Observer<MessageEntityChangeEvent> e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer<MessageEntityChangeEvent> e) {
        observers.remove(e);
    }

    @Override
    public void notifyObservers(MessageEntityChangeEvent t) {
        observers.forEach(observer -> observer.update(t));
    }

    public List<Message> getAllMessages() {
        Iterable<Message> allMessages = messageRepo.findAll();
        List<Message> messagesList = new ArrayList<>();
        allMessages.forEach(messagesList::add);
        return messagesList;
    }

    public List<ReplyMessage> getAllReplies() {
        Iterable<ReplyMessage> allReplies = replyRepo.findAll();
        List<ReplyMessage> replyList = new ArrayList<>();
        allReplies.forEach(replyList::add);
        return replyList;
    }

    public List<Message> getMessagesForUser(String username) {
        Utilizator user = utilizatorService.findbyName(username).orElse(null);
        if (user == null) {
            System.out.println("User not found: " + username);
            return Collections.emptyList();
        }
        System.out.println("Found user: " + user);
        List<Message> allMessages = getAllMessages();
        System.out.println("Total messages retrieved: " + allMessages.size());
        for (Message m : allMessages) {
            System.out.println("Message: " + m);
            for (Utilizator u : m.getUsers()) {
                System.out.println("User in message: " + u);
            }
        }
        List<Message> filteredMessages = allMessages.stream()
                .filter(m -> {
                    boolean containsUser = m.getUsers().contains(user);
                    System.out.println(m.getUsers());;
                    System.out.println("Message contains user " + username + "? " + containsUser);
                    return containsUser;
                })
                .collect(Collectors.toList());
        System.out.println("Filtered messages for user " + username + ": " + filteredMessages.size());

        return filteredMessages;
    }

    public List<Message> getMessagesBetweenUsers(String username1, String username2) {
        Utilizator user2 = utilizatorService.findbyName(username2).orElse(null);
        if (user2 == null) {
            return Collections.emptyList();
        }

        List<Message> user1Messages = getMessagesForUser(username1);
        System.out.println("Mesaje între " + username1 + " și " + username2 + ": " + user1Messages.size());

        return StreamSupport.stream(user1Messages.spliterator(),false).filter(
                message -> {
                    return message.getUserSender().getUsername().equals(user2.getUsername());
                }
        ).collect(Collectors.toList());
    }
    public List<ReplyMessage> getRepliesToUser(String username) {
        Utilizator user = utilizatorService.findbyName(username).orElse(null);
        if (user == null) {
            return Collections.emptyList();
        }

        List<ReplyMessage> allReplies = getAllReplies();
        return allReplies.stream()
                .filter(reply -> reply.getReceiver().getUsername().equals(user.getUsername()))
                .collect(Collectors.toList());
    }

    public List<ReplyMessage> getRepliesBetweenUsers(String username1, String username2) {
        List<ReplyMessage> repliesFromUser1 = getRepliesToUser(username1);
        System.out.println("Răspunsuri între " + username1 + " și " + username2 + ": " + repliesFromUser1.size());

        return repliesFromUser1.stream()
                .filter(reply -> reply.getReplyfor() != null &&
                        reply.getReplyfor().getUserSender().getUsername().equals(username2) &&
                        reply.getReply() != null)
                .collect(Collectors.toList());
    }
    public List<String> getConvo(String username1, String username2) {
        Utilizator user1 = utilizatorService.findbyName(username1).orElse(null);
        Utilizator user2 = utilizatorService.findbyName(username2).orElse(null);

        if (user1 == null || user2 == null) {
            throw new IllegalArgumentException("Ambii utilizatori trebuie să existe!");
        }

        List<Message> user1Messages = getMessagesBetweenUsers(username1, username2);
        List<Message> user2Messages = getMessagesBetweenUsers(username2, username1);
        System.out.println("Mesaje pentru utilizatorul 1: " + user1Messages.size());
        System.out.println("Mesaje pentru utilizatorul 2: " + user2Messages.size());

        List<ReplyMessage> user1Replies = getRepliesBetweenUsers(username1, username2);
        List<ReplyMessage> user2Replies = getRepliesBetweenUsers(username2, username1);
        System.out.println("Răspunsuri pentru utilizatorul 1: " + user1Replies.size());
        System.out.println("Răspunsuri pentru utilizatorul 2: " + user2Replies.size());

        List<Message> allMessages = new ArrayList<>();
        allMessages.addAll(user1Messages);
        allMessages.addAll(user2Messages);
        allMessages.sort(Comparator.comparing(Message::getData));

        List<ReplyMessage> allReplies = new ArrayList<>();
        allReplies.addAll(user1Replies);
        allReplies.addAll(user2Replies);
        allReplies.sort(Comparator.comparing(ReplyMessage::getDataReceiver));

        List<Tuple<String, LocalDateTime>> conversation = new ArrayList<>();
        for (Message message : allMessages) {
            conversation.add(new Tuple<>(message.getUserSender().getUsername() + ": " + message.getMessage(), message.getData()));
        }

        for (ReplyMessage reply : allReplies) {
            if (reply.getReplyfor() != null) {
                int i = 0;
                while (i < conversation.size() && reply.getDataReceiver().compareTo(conversation.get(i).getRight()) > 0) {
                    i++;
                }
                String replyMessage = "\t\t" + reply.getReceiver().getUsername() + " a răspuns la "
                        + reply.getReplyfor().getUserSender().getUsername() + ": " + reply.getReply();
                conversation.add(i, new Tuple<>(replyMessage, reply.getDataReceiver()));
            }
        }

        System.out.println("Conversație finală:");
        conversation.forEach(t -> System.out.println(t.getLeft()));

        return conversation.stream()
                .map(Tuple::getLeft)
                .collect(Collectors.toList());
    }
    private List<Utilizator> getUsersFromNames(String users) {
        List<Utilizator> userList = new ArrayList<>();
        String[] userNames = users.split(" ");
        for (String userName : userNames) {
            Utilizator user = utilizatorService.findbyName(userName).orElse(null);
            if (user == null) {
                throw new IllegalArgumentException("User " + userName + " does not exist!");
            }
            userList.add(user);
        }
        return userList;
    }
    public void addMessage(String senderUsername, String text, String recipients) {
        Utilizator sender = utilizatorService.findbyName(senderUsername).orElse(null);
        if (sender == null) {
            throw new IllegalArgumentException("User " + senderUsername + " does not exist!");
        }
        List<Utilizator> recipientList = getUsersFromNames(recipients);
        Message message = new Message(sender, text, LocalDateTime.now(), recipientList);
        Optional<Message> savedMessage = messageRepo.save(message);
        if (savedMessage.isEmpty()) {
            System.err.println("Error saving message.");
            return;
        }

        message = savedMessage.get();
        for (Utilizator recipient : recipientList) {
            if (!recipient.getId().equals(sender.getId())) {
                ReplyMessage reply = new ReplyMessage(message, recipient, LocalDateTime.now(), null);
                replyRepo.save(reply);
            }
        }
        notifyObservers(new MessageEntityChangeEvent(ChangeEventType.ADD, message));
    }
    public void deleteMessage(Long messageId) {
        messageRepo.delete(messageId);
    }

    public void sendReply(Long messageId, String replyText, String receiverUsername) {
        Utilizator receiver = utilizatorService.findbyName(receiverUsername).orElse(null);
        if (receiver == null) {
            throw new IllegalArgumentException("Receiver does not exist!");
        }

        Message message = messageRepo.findOne(messageId).orElse(null);
        if (message == null) {
            throw new IllegalArgumentException("Message not found!");
        }

        ReplyMessage replyMessage = new ReplyMessage(message, receiver, LocalDateTime.now(), replyText);
        replyRepo.save(replyMessage);
    }
}
