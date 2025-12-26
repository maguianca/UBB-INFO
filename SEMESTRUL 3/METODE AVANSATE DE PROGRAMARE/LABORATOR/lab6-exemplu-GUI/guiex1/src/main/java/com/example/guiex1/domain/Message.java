package com.example.guiex1.domain;

import java.time.LocalDateTime;

public class Message {
    private Utilizator sender;
    private Utilizator receiver;
    private String messageContent;
    private LocalDateTime sendDate;
    private Message inReplyTo;

    public Message(Utilizator sender, Utilizator receiver, String messageContent, LocalDateTime sendDate, Message inReplyTo) {
        this.sender = sender;
        this.receiver = receiver;
        this.messageContent = messageContent;
        this.sendDate = sendDate;
        this.inReplyTo = inReplyTo;
    }

    public Utilizator getSender() {
        return sender;
    }

    public void setSender(Utilizator sender) {
        this.sender = sender;
    }

    public Utilizator getReceiver() {
        return receiver;
    }

    public void setReceiver(Utilizator receiver) {
        this.receiver = receiver;
    }

    public String getMessageContent() {
        return messageContent;
    }

    public void setMessageContent(String messageContent) {
        this.messageContent = messageContent;
    }

    public LocalDateTime getSendDate() {
        return sendDate;
    }

    public void setSendDate(LocalDateTime sendDate) {
        this.sendDate = sendDate;
    }

    public Message getInReplyTo() {
        return inReplyTo;
    }

    public void setInReplyTo(Message inReplyTo) {
        this.inReplyTo = inReplyTo;
    }
}
