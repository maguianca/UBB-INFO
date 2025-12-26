package com.example.guiex1.domain;

import java.time.LocalDateTime;
import java.util.Objects;

public class ReplyMessage extends Entity<Tuple<Long,Long>> {
    private Message replyfor;
    private Utilizator reciever;
    private LocalDateTime dataReceiver;
    private String reply;

    public ReplyMessage(Message replyfor, Utilizator reciever, LocalDateTime dataReciever, String reply) {
        this.replyfor = replyfor;
        this.reciever = reciever;
        this.dataReceiver = dataReciever;
        this.reply = reply;
        Long idM=replyfor.getId();
        Long idU=reciever.getId();
        Tuple<Long, Long> Tuple=new Tuple(idM,idU);
        this.setId(Tuple);
    }

    @Override
    public String toString() {
        return "ReplyMessage{" +
                "replyfor=" + replyfor.getUserSender().getFirstName() +" "+ replyfor.getUserSender().getLastName() +
                ", reciever=" + reciever.getFirstName() +" "+ reciever.getLastName() +
                ", dataReceiver=" + dataReceiver.toString() +
                ", reply='" + reply + '\'' +
                '}';
    }

    public Message getReplyfor() {
        return replyfor;
    }

    public void setReplyfor(Message replyfor) {
        this.replyfor = replyfor;
    }

    public Utilizator getReceiver() {
        return reciever;
    }

    public void setReciever(Utilizator reciever) {
        this.reciever = reciever;
    }

    public LocalDateTime getDataReceiver() {
        return dataReceiver;
    }

    public void setDataReciever(LocalDateTime dataReciever) {
        this.dataReceiver = dataReciever;
    }

    public String getReply() {
        return reply;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof ReplyMessage that)) return false;
        if (!super.equals(o)) return false;
        return Objects.equals(getReplyfor(), that.getReplyfor()) && Objects.equals(getReceiver(), that.getReceiver()) && Objects.equals(getDataReceiver(), that.getDataReceiver()) && Objects.equals(getReply(), that.getReply());
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), getReplyfor(), getReceiver(), getDataReceiver(), getReply());
    }

    public void setReply(String reply) {
        this.reply = reply;
    }

}