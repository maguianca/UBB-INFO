using Npgsql;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace Laborator13
{
    internal class RepoJucator : IRepository<int, Jucator>
    {
        private readonly string _connectionString;
        private IRepository<int, Echipa> RepoEchipa;

        public RepoJucator(string connectionString, IRepository<int, Echipa> repoEchipa)
        {
            _connectionString = connectionString;
            RepoEchipa = repoEchipa;
        }

        public Jucator FindOne(int id)
        {
            try
            {
                if (id == 0) throw new ArgumentException("ID-ul nu poate fi null sau zero.");

                using (var connection = new NpgsqlConnection(_connectionString))
                {
                    connection.Open();

                    var query = "SELECT * FROM jucator WHERE id = @Id";
                    using (var command = new NpgsqlCommand(query, connection))
                    {
                        command.Parameters.AddWithValue("@id", id);

                        using (var reader = command.ExecuteReader())
                        {
                            if (reader.Read())
                            {
                                int id_echipa = reader.GetInt32(3);
                                Echipa echipa = RepoEchipa.FindOne(id_echipa);
                                return new Jucator(reader.GetInt32(0), reader.GetString(1), reader.GetString(2), echipa);
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

        public IEnumerable<Jucator> FindAll()
        {
            var jucatori = new List<Jucator>();

            try
            {
                using (var connection = new NpgsqlConnection(_connectionString))
                {
                    connection.Open();

                    var query = "SELECT * FROM jucator";
                    using (var command = new NpgsqlCommand(query, connection))
                    {
                        using (var reader = command.ExecuteReader())
                        {
                            while (reader.Read())
                            {
                                int id_echipa = reader.GetInt32(3);
                                Echipa echipa = RepoEchipa.FindOne(id_echipa);
                                jucatori.Add(new Jucator(reader.GetInt32(0), reader.GetString(1), reader.GetString(2), echipa));
                            }
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Eroare în FindAll: {ex.Message}");
            }

            return jucatori;
        }

        public Jucator Save(Jucator entity)
        {
            try
            {
                if (entity == null) throw new ArgumentException("Entitatea nu poate fi null.");
                if (entity.Id == 0) throw new ValidationException("ID-ul nu poate fi zero.");
                if (string.IsNullOrEmpty(entity.elev_nume)) throw new ValidationException("Numele nu poate fi gol.");
                if (string.IsNullOrEmpty(entity.elev_scoala)) throw new ValidationException("Școala nu poate fi goală.");
                if (entity.echipa.Id == 0) throw new ValidationException("Echipa nu poate fi goală.");

                using (var connection = new NpgsqlConnection(_connectionString))
                {
                    connection.Open();

                    var query = "INSERT INTO jucator (nume, scoala, echipa) VALUES (@Id, @Nume, @Scoala, @Echipa)";
                    using (var command = new NpgsqlCommand(query, connection))
                    {
                        command.Parameters.AddWithValue("@Id", entity.Id);
                        command.Parameters.AddWithValue("@Nume", entity.elev_nume);
                        command.Parameters.AddWithValue("@Scoala", entity.elev_scoala);
                        command.Parameters.AddWithValue("@Echipa", entity.echipa);

                        command.ExecuteNonQuery();
                        return null;
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Eroare în Save: {ex.Message}");
                return entity;
            }
        }

        public Jucator Delete(int id)
        {
            try
            {
                if (id == 0) throw new ArgumentException("ID-ul nu poate fi null sau zero.");

                using (var connection = new NpgsqlConnection(_connectionString))
                {
                    connection.Open();

                    var query = "DELETE FROM jucator WHERE id = @Id";
                    using (var command = new NpgsqlCommand(query, connection))
                    {
                        command.Parameters.AddWithValue("@Id", id);

                        using (var reader = command.ExecuteReader())
                        {
                            if (reader.Read())
                            {
                                int id_echipa = reader.GetInt32(3);
                                Echipa echipa = RepoEchipa.FindOne(id_echipa);
                                return new Jucator(reader.GetInt32(0), reader.GetString(1), reader.GetString(2), echipa);
                            }
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

        public Jucator Update(Jucator entity)
        {
            try
            {
                if (entity == null) throw new ArgumentException("Entitatea nu poate fi null.");
                if (entity.Id == 0) throw new ValidationException("ID-ul nu poate fi zero.");
                if (string.IsNullOrEmpty(entity.elev_nume)) throw new ValidationException("Numele nu poate fi gol.");
                if (string.IsNullOrEmpty(entity.elev_scoala)) throw new ValidationException("Școala nu poate fi goală.");
                if (entity.echipa.Id == 0) throw new ValidationException("Echipa nu poate fi goală.");

                using (var connection = new NpgsqlConnection(_connectionString))
                {
                    connection.Open();

                    var query = "UPDATE jucator SET nume = @Nume, scoala = @Scoala, echipa = @Echipa WHERE id = @Id";
                    using (var command = new NpgsqlCommand(query, connection))
                    {
                        command.Parameters.AddWithValue("@Nume", entity.elev_nume);
                        command.Parameters.AddWithValue("@Scoala", entity.elev_scoala);
                        command.Parameters.AddWithValue("@Echipa", entity.echipa);

                        using (var reader = command.ExecuteReader())
                        {
                            if (reader.Read())
                            {
                                return null;
                            }
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
