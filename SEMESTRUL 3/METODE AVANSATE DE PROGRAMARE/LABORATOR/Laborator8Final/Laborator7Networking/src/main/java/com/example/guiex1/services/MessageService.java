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

    // Get all messages for a specific user
    public List<Message> getMessagesForUser(String username) {
        // Find the user by username
        Utilizator user = utilizatorService.findbyName(username).orElse(null);
        if (user == null) {
            // If no user is found, return an empty list
            System.out.println("User not found: " + username);
            return Collections.emptyList();
        }

        // Debug: Print the user found
        System.out.println("Found user: " + user);

        // Retrieve all messages
        List<Message> allMessages = getAllMessages();
        System.out.println("Total messages retrieved: " + allMessages.size());

        // Debug: Log all messages and check their user lists
        for (Message m : allMessages) {
            System.out.println("Message: " + m);  // Logs each message's details
            for (Utilizator u : m.getUsers()) {
                System.out.println("User in message: " + u); // Logs each user in the message
            }
        }

        // Filter messages where the user is part of the message's 'users' list
        List<Message> filteredMessages = allMessages.stream()
                .filter(m -> {
                    // Check if the message contains the target user
                    boolean containsUser = m.getUsers().contains(user);
                    System.out.println(m.getUsers());;
                    System.out.println("Message contains user " + username + "? " + containsUser);
                    return containsUser;
                })
                .collect(Collectors.toList());

        // Debug: Output the filtered messages
        System.out.println("Filtered messages for user " + username + ": " + filteredMessages.size());

        return filteredMessages;
    }



    // Get messages exchanged between two users
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


    // Get replies sent to a specific user
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

    // Get replies exchanged between two users
    public List<ReplyMessage> getRepliesBetweenUsers(String username1, String username2) {
        List<ReplyMessage> repliesFromUser1 = getRepliesToUser(username1);
        System.out.println("Răspunsuri între " + username1 + " și " + username2 + ": " + repliesFromUser1.size());

        return repliesFromUser1.stream()
                .filter(reply -> reply.getReplyfor() != null &&
                        reply.getReplyfor().getUserSender().getUsername().equals(username2) &&
                        reply.getReply() != null)
                .collect(Collectors.toList());
    }

    // Get the entire conversation between two users, including messages and replies
    public List<String> getConvo(String username1, String username2) {
        Utilizator user1 = utilizatorService.findbyName(username1).orElse(null);
        Utilizator user2 = utilizatorService.findbyName(username2).orElse(null);

        if (user1 == null || user2 == null) {
            throw new IllegalArgumentException("Ambii utilizatori trebuie să existe!");
        }

        // Obține mesajele
        List<Message> user1Messages = getMessagesBetweenUsers(username1, username2);
        List<Message> user2Messages = getMessagesBetweenUsers(username2, username1);
        System.out.println("Mesaje pentru utilizatorul 1: " + user1Messages.size());
        System.out.println("Mesaje pentru utilizatorul 2: " + user2Messages.size());

        // Obține răspunsurile
        List<ReplyMessage> user1Replies = getRepliesBetweenUsers(username1, username2);
        List<ReplyMessage> user2Replies = getRepliesBetweenUsers(username2, username1);
        System.out.println("Răspunsuri pentru utilizatorul 1: " + user1Replies.size());
        System.out.println("Răspunsuri pentru utilizatorul 2: " + user2Replies.size());

        // Combină toate mesajele și răspunsurile
        List<Message> allMessages = new ArrayList<>();
        allMessages.addAll(user1Messages);
        allMessages.addAll(user2Messages);
        allMessages.sort(Comparator.comparing(Message::getData));

        List<ReplyMessage> allReplies = new ArrayList<>();
        allReplies.addAll(user1Replies);
        allReplies.addAll(user2Replies);
        allReplies.sort(Comparator.comparing(ReplyMessage::getDataReceiver));

        // Creează conversația
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

        // Debugging conversație
        System.out.println("Conversație finală:");
        conversation.forEach(t -> System.out.println(t.getLeft()));

        return conversation.stream()
                .map(Tuple::getLeft)
                .collect(Collectors.toList());
    }


    // Helper method to convert a space-separated list of usernames into a list of users
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

    // Add a new message to the system
    public void addMessage(String senderUsername, String text, String recipients) {
        Utilizator sender = utilizatorService.findbyName(senderUsername).orElse(null);
        if (sender == null) {
            throw new IllegalArgumentException("User " + senderUsername + " does not exist!");
        }

        // Get recipient list
        List<Utilizator> recipientList = getUsersFromNames(recipients);
        Message message = new Message(sender, text, LocalDateTime.now(), recipientList);

        // Save the message and handle any existing messages
        Optional<Message> savedMessage = messageRepo.save(message);
        if (savedMessage.isEmpty()) {
            // If saving fails, handle it accordingly
            System.err.println("Error saving message.");
            return;
        }

        message = savedMessage.get();  // Use the saved message with the generated ID

        // Create and save replies for each recipient
        for (Utilizator recipient : recipientList) {
            // Ensure replies are created only if the recipient is not the sender
            if (!recipient.getId().equals(sender.getId())) {
                ReplyMessage reply = new ReplyMessage(message, recipient, LocalDateTime.now(), null);
                replyRepo.save(reply);
            }
        }

        // Notify observers of the new message
        notifyObservers(new MessageEntityChangeEvent(ChangeEventType.ADD, message));
    }

    // Delete a message by its ID
    public void deleteMessage(Long messageId) {
        messageRepo.delete(messageId);
    }

    // Send a reply to a specific message
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
