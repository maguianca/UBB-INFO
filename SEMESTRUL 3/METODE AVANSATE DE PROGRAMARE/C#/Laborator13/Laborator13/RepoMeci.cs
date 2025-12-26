using Npgsql;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace Laborator13
{
    internal class RepoMeci : IRepository<int, Meci>
    {
        private readonly string _connectionString;
        private IRepository<int, Echipa> RepoEchipa;

        public RepoMeci(string connectionString, IRepository<int, Echipa> repoEchipa)
        {
            _connectionString = connectionString;
            RepoEchipa = repoEchipa;
        }

        public Meci FindOne(int id)
        {
            if (id == 0) throw new ArgumentException("ID-ul nu poate fi null sau zero.");

            try
            {
                using (var connection = new NpgsqlConnection(_connectionString))
                {
                    connection.Open();

                    var query = "SELECT * FROM meci WHERE id = @Id";
                    using (var command = new NpgsqlCommand(query, connection))
                    {
                        command.Parameters.AddWithValue("@Id", id);

                        using (var reader = command.ExecuteReader())
                        {
                            if (reader.Read())
                            {
                                Echipa echipa1 = RepoEchipa.FindOne(reader.GetInt32(1));
                                Echipa echipa2 = RepoEchipa.FindOne(reader.GetInt32(2));
                                var data = reader.GetDateTime(3);
                                return new Meci(reader.GetInt32(0), echipa1, echipa2, data);
                            }
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Eroare în FindOne: {ex.Message}");
            }

            return null;
        }

        public IEnumerable<Meci> FindAll()
        {
            var meciuri = new List<Meci>();

            try
            {
                using (var connection = new NpgsqlConnection(_connectionString))
                {
                    connection.Open();

                    var query = "SELECT * FROM meci";
                    using (var command = new NpgsqlCommand(query, connection))
                    {
                        using (var reader = command.ExecuteReader())
                        {
                            while (reader.Read())
                            {
                                Echipa echipa1 = RepoEchipa.FindOne(reader.GetInt32(1));
                                Echipa echipa2 = RepoEchipa.FindOne(reader.GetInt32(2));
                                var data = reader.GetDateTime(3);
                                meciuri.Add(new Meci(reader.GetInt32(0), echipa1, echipa2, data));
                            }
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Eroare în FindAll: {ex.Message}");
            }

            return meciuri;
        }

        public Meci Save(Meci entity)
        {
            if (entity == null) throw new ArgumentException("Entitatea nu poate fi null.");
            if (entity.Id == 0) throw new ValidationException("ID-ul nu poate fi zero.");

            try
            {
                using (var connection = new NpgsqlConnection(_connectionString))
                {
                    connection.Open();

                    var query = "INSERT INTO meci (echipa1id, echipa2id, data) VALUES (@Echipa1Id, @Echipa2Id, @Data)";
                    using (var command = new NpgsqlCommand(query, connection))
                    {
                        command.Parameters.AddWithValue("@Echipa1Id", entity.Echipa1.Id);
                        command.Parameters.AddWithValue("@Echipa2Id", entity.Echipa2.Id);
                        command.Parameters.AddWithValue("@Data", entity.Data);

                        command.ExecuteNonQuery();
                    }
                }

                return entity; 
            }
            catch (NpgsqlException ex)
            {
                Console.WriteLine($"Eroare în Save: {ex.Message}");
                return null;
            }
        }

        public Meci Delete(int id)
        {
            if (id == 0) throw new ArgumentException("ID-ul nu poate fi null sau zero.");

            try
            {
                using (var connection = new NpgsqlConnection(_connectionString))
                {
                    connection.Open();

                    var query = "DELETE FROM meci WHERE id = @Id";
                    using (var command = new NpgsqlCommand(query, connection))
                    {
                        command.Parameters.AddWithValue("@Id", id);

                        int affectedRows = command.ExecuteNonQuery();
                        if (affectedRows > 0)
                        {
                            return new Meci(id, null, null, DateTime.MinValue); 
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Eroare în Delete: {ex.Message}");
            }

            return null;
        }

        public Meci Update(Meci entity)
        {
            if (entity == null) throw new ArgumentException("Entitatea nu poate fi null.");
            if (entity.Id == 0) throw new ValidationException("ID-ul nu poate fi zero.");

            try
            {
                using (var connection = new NpgsqlConnection(_connectionString))
                {
                    connection.Open();

                    var query = "UPDATE meci SET echipa1id = @Echipa1Id, echipa2id = @Echipa2Id, data = @Data WHERE id = @Id";
                    using (var command = new NpgsqlCommand(query, connection))
                    {
                        command.Parameters.AddWithValue("@Id", entity.Id);
                        command.Parameters.AddWithValue("@Echipa1Id", entity.Echipa1.Id);
                        command.Parameters.AddWithValue("@Echipa2Id", entity.Echipa2.Id);
                        command.Parameters.AddWithValue("@Data", entity.Data);

                        int affectedRows = command.ExecuteNonQuery();
                        if (affectedRows > 0)
                        {
                            return null; 
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Eroare în Update: {ex.Message}");
            }

            return entity;
        }
    }
}
