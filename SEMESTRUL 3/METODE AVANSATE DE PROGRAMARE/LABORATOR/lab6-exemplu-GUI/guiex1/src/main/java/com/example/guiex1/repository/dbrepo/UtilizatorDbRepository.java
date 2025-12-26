package com.example.guiex1.repository.dbrepo;

import com.example.guiex1.domain.*;
import com.example.guiex1.repository.Repository;


import java.sql.*;
import java.time.LocalDate;
import java.util.*;
import java.sql.Date;

public class UtilizatorDbRepository implements Repository<Long, Utilizator> {
    private String url;
    private String username;
    private String password;
    private Validator<Utilizator> validator;

    public UtilizatorDbRepository(String url, String username, String password, Validator<Utilizator> validator) {
        this.url = url;
        this.username = username;
        this.password = password;
        this.validator = validator;
    }

    /**
     * @param id - long, the id of a user to found
     * @return Optional<User> - the user with the given id
     *                        -Optional.empty() otherwise
     */
    @Override
    public Optional<Utilizator> findOne(Long id) {
        Utilizator user;
        try(Connection connection = DriverManager.getConnection(url, username, password);
            ResultSet resultSet = connection.createStatement().executeQuery(String.format("select * from users U where U.id = '%d'", id))) {
            if(resultSet.next()){
                user = createUserFromResultSet(resultSet);
                return Optional.ofNullable(user);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    public Optional<Utilizator> findOne(String firstName,String lastName, String passwrd){
        Utilizator user;
        try(Connection connection = DriverManager.getConnection(url,username,password);
            ResultSet resultSet = connection.createStatement().executeQuery(String.format("select * from users U where U.first_name = '%s' AND U.last_name = '%s' AND U.password = '%s'", firstName,lastName,passwrd))) {
            if(resultSet.next()){
                user = createUserFromResultSet(resultSet);
                return Optional.ofNullable(user);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    public Optional<Utilizator> findOne(String firstName,String lastName){
        Utilizator user;
        try(Connection connection = DriverManager.getConnection(url,username,password);
            ResultSet resultSet = connection.createStatement().executeQuery(String.format("select * from users U where U.first_name = '%s' AND U.last_name = '%s'", firstName,lastName))) {
            if(resultSet.next()){
                user = createUserFromResultSet(resultSet);
                return Optional.ofNullable(user);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    public List<Long> getFriendRequestForUserId(Long userId){
        ArrayList<Long> usersWhoRequestedFriendshipIds = new ArrayList<>();

        String query = "SELECT * FROM friend_requests WHERE receives_friendship_id = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setLong(1, userId);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    long userIdRequestedFriendship = resultSet.getLong("requests_friendship_id");
                    usersWhoRequestedFriendshipIds.add(userIdRequestedFriendship);
                }
                return usersWhoRequestedFriendshipIds.stream()
                        .distinct()
                        .toList();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        //return usersWhoRequestedFriendshipIds;
        return Collections.emptyList();
    }

    public List<friendRequestDTO> getFriendRequestWithDateForUserId(Long userId){
        ArrayList<friendRequestDTO> usersWhoRequestedFriendshipIds = new ArrayList<>();

        String query = "SELECT * FROM friend_requests WHERE receives_friendship_id = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setLong(1, userId);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    long userIdRequestedFriendship = resultSet.getLong("requests_friendship_id");
                    Date requestDate = resultSet.getDate("request_date");
                    LocalDate requestDateCorrectFormat = requestDate.toLocalDate();
                    usersWhoRequestedFriendshipIds.add(new friendRequestDTO(requestDateCorrectFormat,userIdRequestedFriendship));
                }
                return usersWhoRequestedFriendshipIds.stream()
                        .sorted(Comparator.comparing(friendRequestDTO::getRequestDate))
                        .toList();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        //return usersWhoRequestedFriendshipIds;
        return Collections.emptyList();
    }

    public List<Long> getFriendsForUserId(Long userId){
        ArrayList<Long> friendIds = new ArrayList<>();

        String query = "SELECT * FROM prietenii WHERE first_user_id = ? OR second_user_id = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setLong(1, userId);
            preparedStatement.setLong(2, userId);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    long firstUserId = resultSet.getLong("first_user_id");
                    long secondUserId = resultSet.getLong("second_user_id");
                    friendIds.add((firstUserId != userId) ? firstUserId : secondUserId);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return friendIds;
    }
    public Page<Long> getPagedFriendsForUserID(Long id, Pageable pageable){
        ArrayList<Long> friendIds = new ArrayList<>();
        String queryTotalNumberOfElements = "SELECT COUNT(*) AS count FROM prietenii WHERE first_user_id = ? OR second_user_id = ?";
        String query = "SELECT * FROM prietenii WHERE first_user_id = ? OR second_user_id = ? LIMIT ? OFFSET ?";
        Integer count=0;
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement preparedStatement = connection.prepareStatement(query);
             PreparedStatement preparedStatementCount = connection.prepareStatement(queryTotalNumberOfElements)) {


            preparedStatement.setLong(1, id);
            preparedStatement.setLong(2, id);

            int offset = (pageable.getPageNumber() - 1) * pageable.getPageSize();
            preparedStatement.setInt(3,pageable.getPageSize());
            preparedStatement.setInt(4,offset);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    long firstUserId = resultSet.getLong("first_user_id");
                    long secondUserId = resultSet.getLong("second_user_id");
                    friendIds.add((firstUserId != id) ? firstUserId : secondUserId);
                }
            }
            preparedStatementCount.setLong(1,id);
            preparedStatementCount.setLong(2,id);

            try(ResultSet resultSet = preparedStatementCount.executeQuery()){
                while(resultSet.next()) {
                    count = resultSet.getInt("count");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return new Page<>(count, friendIds);
    }

    private Utilizator createUserFromResultSet(ResultSet resultSet) {
        try {
            String firstName = resultSet.getString("first_name");
            String lastName = resultSet.getString("last_name");
            String password = resultSet.getString("password");
            Long idd = resultSet.getLong("id");
            List<Long> friendList = getFriendsForUserId(idd);
            Utilizator user = new Utilizator(firstName, lastName,password,friendList);
            user.setId(idd);
            return user;
        } catch (SQLException e) {
            return null;
        }
    }

    @Override
    public Iterable<Utilizator> findAll() {
        Set<Utilizator> users = new HashSet<>();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("SELECT * from users");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");
                String firstName = resultSet.getString("first_name");
                String lastName = resultSet.getString("last_name");
                String password = resultSet.getString("password");

                Utilizator utilizator = new Utilizator(firstName, lastName,password);
                utilizator.setId(id);
                users.add(utilizator);
            }
            return users;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return users;
    }
    public List<Long> getAllUserIds(){
        List<Long> usersIDs = new ArrayList<>();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("SELECT id from users");
             ResultSet resultSet = statement.executeQuery()) {

            while (resultSet.next()) {
                Long id = resultSet.getLong("id");

                usersIDs.add(id);
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return usersIDs;
    }
    @Override
    public Optional<Utilizator> save(Utilizator entity) {
        String sql = "insert into users (first_name, last_name, password) values (?, ?, ?)";
        validator.validate(entity);
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement ps = connection.prepareStatement(sql)) {

            ps.setString(1, entity.getFirstName());
            ps.setString(2, entity.getLastName());
            ps.setString(3,entity.getPassword());

            ps.executeUpdate();
        } catch (SQLException e) {
            //e.printStackTrace();
            return Optional.ofNullable(entity);
        }
        return Optional.empty();
    }

    @Override
    public Optional<Utilizator> delete(Long id) {
        String sql = "delete from users where id = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement ps = connection.prepareStatement(sql)) {
            Optional<Utilizator> user = findOne(id);
            if(!user.isEmpty()) {
                ps.setLong(1, id);
                ps.executeUpdate();
            }
            return user;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    @Override
    public Optional<Utilizator> update(Utilizator user) {
        if(user == null)
            throw new IllegalArgumentException("entity must be not null!");
        validator.validate(user);
        String sql = "update users set first_name = ?, last_name = ?, password = ? where id = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setString(1,user.getFirstName());
            ps.setString(2, user.getLastName());
            ps.setString(3,user.getPassword());
            ps.setLong(4, user.getId());
            if( ps.executeUpdate() > 0 )
                return Optional.empty();
            return Optional.ofNullable(user);
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return Optional.empty();
    }

    public void deleteFriendship(Long firstId, Long secondId) {
        String query = "DELETE FROM prietenii WHERE first_user_id = ? AND second_user_id = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setLong(1, firstId);
            preparedStatement.setLong(2, secondId);

            int rowsDeleted = preparedStatement.executeUpdate();
            if (rowsDeleted == 0) {
                preparedStatement.setLong(1, secondId);
                preparedStatement.setLong(2, firstId);
                preparedStatement.executeUpdate();
            }
        }catch (SQLException e){
            e.printStackTrace();
        }

    }

    public void deleteFriendRequest(Long userToAcceptFriendshipRequestId, Long userId) {
        String sql = "delete from friend_requests where requests_friendship_id = ? AND receives_friendship_id = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setLong(1,userToAcceptFriendshipRequestId);
            ps.setLong(2,userId);
            ps.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void addFriendship(Long firstId, Long secondId, LocalDate friendsFrom) {
        String sql = "insert into prietenii(first_user_id, second_user_id, friends_from) values (?, ?, ?)";
        try(Connection connection = DriverManager.getConnection(url,username,password);
            PreparedStatement ps = connection.prepareStatement(sql)){
            ps.setLong(1,firstId);
            ps.setLong(2,secondId);
            ps.setObject(3,friendsFrom);
            ps.executeUpdate();
        }catch (SQLException e){
            e.printStackTrace();
        }
    }

    public void addFriendshipRequest(Long idWhoRequests, Long toWhomIRequest, LocalDate date) {
        String sql = "insert into friend_requests(requests_friendship_id, receives_friendship_id, request_date) values (?, ?, ?)";
        try(Connection connection = DriverManager.getConnection(url,username,password);
            PreparedStatement ps = connection.prepareStatement(sql)){
            ps.setLong(1,idWhoRequests);
            ps.setLong(2,toWhomIRequest);
            ps.setObject(3,date);
            ps.executeUpdate();
        }catch (SQLException e){
            e.printStackTrace();
        }
    }

    public List<Long> idsOfUsersIRequestedFriendshipFrom(Long id){
        ArrayList<Long> usersWhoRequestedFriendshipIds = new ArrayList<>();

        String query = "SELECT * FROM friend_requests WHERE requests_friendship_id = ?";
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement preparedStatement = connection.prepareStatement(query)) {

            preparedStatement.setLong(1, id);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    long userIdRequestedFriendship = resultSet.getLong("receives_friendship_id");
                    usersWhoRequestedFriendshipIds.add(userIdRequestedFriendship);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return usersWhoRequestedFriendshipIds;
    }

    private Message createMessageFromResultSet(ResultSet rs) throws SQLException {
        Long senderId = rs.getLong("sender_id");
        Long receiverId = rs.getLong("receiver_id");
        Timestamp sendDate = rs.getTimestamp("send_date");
        String messageContent = rs.getString("message_content");

        return new Message(findOne(senderId).get(),findOne(receiverId).get(), messageContent,sendDate.toLocalDateTime(),null);
    }

    public List<Message> getMessages(Long firstId, Long secondId) {
        List<Message> messageList = new ArrayList<>();
        String query = "SELECT * FROM messages WHERE (sender_id = ? AND receiver_id = ?) OR (sender_id = ? AND receiver_id = ?)";
        try(Connection connection = DriverManager.getConnection(url,username,password);
            PreparedStatement ps = connection.prepareStatement(query)){
            ps.setLong(1,firstId);
            ps.setLong(2,secondId);
            ps.setLong(3,secondId);
            ps.setLong(4,firstId);
            ResultSet resultSet = ps.executeQuery();
            while(resultSet.next()){
                messageList.add(createMessageFromResultSet(resultSet));
            }
        }catch(SQLException e){
            e.printStackTrace();
        }
        return messageList;
    }
    public void addMessage(Message message){
        String query = "INSERT INTO messages(sender_id, receiver_id, send_date, in_reply_to, message_content) VALUES (?,?,?,?,?)";
        try(Connection connection = DriverManager.getConnection(url,username,password);
            PreparedStatement ps = connection.prepareStatement(query)){
            ps.setLong(1,message.getSender().getId());
            ps.setLong(2,message.getReceiver().getId());
            ps.setTimestamp(3,Timestamp.valueOf(message.getSendDate()));
            ps.setNull(4,Types.BIGINT);
            ps.setString(5,message.getMessageContent());

            ps.executeUpdate();

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
