using Npgsql;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace Laborator13
{
    internal class RepoElev : IRepository<int, Elev>
    {
        private readonly string _connectionString;

        public RepoElev(string connectionString)
        {
            _connectionString = connectionString;
        }

        public Elev FindOne(int id)
        {
            try
            {
                if (id == 0) throw new ArgumentException("ID-ul nu poate fi null sau zero.");

                using (var connection = new NpgsqlConnection(_connectionString))
                {
                    connection.Open();

                    var query = "SELECT * FROM elev WHERE id = @Id";
                    using (var command = new NpgsqlCommand(query, connection))
                    {
                        command.Parameters.AddWithValue("@id", id);

                        using (var reader = command.ExecuteReader())
                        {
                            if (reader.Read())
                            {
                                return new Elev(reader.GetInt32(0), reader.GetString(1), reader.GetString(2));
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

        public IEnumerable<Elev> FindAll()
        {
            var elevi = new List<Elev>();

            try
            {
                using (var connection = new NpgsqlConnection(_connectionString))
                {
                    connection.Open();

                    var query = "SELECT * FROM elev";
                    using (var command = new NpgsqlCommand(query, connection))
                    {
                        using (var reader = command.ExecuteReader())
                        {
                            while (reader.Read())
                            {
                                elevi.Add(new Elev(reader.GetInt32(0), reader.GetString(1), reader.GetString(2)));
                            }
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Eroare în FindAll: {ex.Message}");
            }

            return elevi;
        }

        public Elev Save(Elev entity)
        {
            try
            {
                if (entity == null) throw new ArgumentException("Entitatea nu poate fi null.");
                if (entity.Id == 0) throw new ValidationException("ID-ul nu poate fi zero.");
                if (string.IsNullOrEmpty(entity.elev_nume)) throw new ValidationException("Numele nu poate fi gol.");
                if (string.IsNullOrEmpty(entity.elev_scoala)) throw new ValidationException("Școala nu poate fi goală.");

                using (var connection = new NpgsqlConnection(_connectionString))
                {
                    connection.Open();

                    var query = "INSERT INTO elev (nume, scoala) VALUES (@nume, @scoala)";
                    using (var command = new NpgsqlCommand(query, connection))
                    {
                        command.Parameters.AddWithValue("@nume", entity.elev_nume);
                        command.Parameters.AddWithValue("@scoala", entity.elev_scoala);

                        command.ExecuteNonQuery();
                        return null;
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Eroare în Save: {ex.Message}");
            }

            return entity;
        }

        public Elev Delete(int id)
        {
            try
            {
                if (id == 0) throw new ArgumentException("ID-ul nu poate fi null sau zero.");

                using (var connection = new NpgsqlConnection(_connectionString))
                {
                    connection.Open();

                    var query = "DELETE FROM elev WHERE id = @id";
                    using (var command = new NpgsqlCommand(query, connection))
                    {
                        command.Parameters.AddWithValue("@id", id);

                        using (var reader = command.ExecuteReader())
                        {
                            if (reader.Read())
                            {
                                return new Elev(reader.GetInt32(0), reader.GetString(1), reader.GetString(2));
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

        public Elev Update(Elev entity)
        {
            try
            {
                if (entity == null) throw new ArgumentException("Entitatea nu poate fi null.");
                if (entity.Id == 0) throw new ValidationException("ID-ul nu poate fi zero.");
                if (string.IsNullOrEmpty(entity.elev_nume)) throw new ValidationException("Numele nu poate fi gol.");
                if (string.IsNullOrEmpty(entity.elev_scoala)) throw new ValidationException("Școala nu poate fi goală.");

                using (var connection = new NpgsqlConnection(_connectionString))
                {
                    connection.Open();

                    var query = "UPDATE elev SET nume = @nume, scoala = @scoala WHERE id = @id";
                    using (var command = new NpgsqlCommand(query, connection))
                    {
                        command.Parameters.AddWithValue("@id", entity.Id);
                        command.Parameters.AddWithValue("@nume", entity.elev_nume);
                        command.Parameters.AddWithValue("@scoala", entity.elev_scoala);

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
