using Npgsql;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace Laborator13
{
    internal class RepoEchipa : IRepository<int, Echipa>
    {
        private readonly string _connectionString;

        public RepoEchipa(string connectionString)
        {
            _connectionString = connectionString;
        }

        public Echipa FindOne(int id)
        {
            if (id == 0) throw new ArgumentException("ID-ul nu poate fi null sau zero.");
            try
            {
                using (var connection = new NpgsqlConnection(_connectionString))
                {
                    connection.Open();

                    var query = "SELECT * FROM echipa WHERE id = @id";
                    using (var command = new NpgsqlCommand(query, connection))
                    {
                        command.Parameters.AddWithValue("@id", id);

                        using (var reader = command.ExecuteReader())
                        {
                            if (reader.Read())
                            {
                                return new Echipa(reader.GetInt32(0), reader.GetString(1));
                            }
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Eroare la FindOne: {ex.Message}");
            }
            return null;
        }

        public IEnumerable<Echipa> FindAll()
        {
            var echipe = new List<Echipa>();
            try
            {
                using (var connection = new NpgsqlConnection(_connectionString))
                {
                    connection.Open();

                    var query = "SELECT * FROM echipa";
                    using (var command = new NpgsqlCommand(query, connection))
                    {
                        using (var reader = command.ExecuteReader())
                        {
                            while (reader.Read())
                            {
                                echipe.Add(new Echipa(reader.GetInt32(0), reader.GetString(1)));
                            }
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Eroare la FindAll: {ex.Message}");
            }

            return echipe;
        }

        public Echipa Save(Echipa entity)
        {
            if (entity == null) throw new ArgumentException("Entitatea nu poate fi null.");
            if (entity.Id == 0) throw new ValidationException("ID-ul nu poate fi zero.");
            if (string.IsNullOrEmpty(entity.echipa_nume)) throw new ValidationException("Numele nu poate fi gol.");

            try
            {
                using (var connection = new NpgsqlConnection(_connectionString))
                {
                    connection.Open();

                    var query = "INSERT INTO echipa(nume) VALUES (@nume)";
                    using (var command = new NpgsqlCommand(query, connection))
                    {
                        command.Parameters.AddWithValue("@nume", entity.echipa_nume);

                        command.ExecuteNonQuery();
                        return null; 
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Eroare la Save: {ex.Message}");
            }

            return entity; 
        }

        public Echipa Delete(int id)
        {
            if (id == 0) throw new ArgumentException("ID-ul nu poate fi null sau zero.");

            try
            {
                using (var connection = new NpgsqlConnection(_connectionString))
                {
                    connection.Open();

                    var query = "DELETE FROM echipa WHERE id = @id RETURNING *";
                    using (var command = new NpgsqlCommand(query, connection))
                    {
                        command.Parameters.AddWithValue("@id", id);

                        using (var reader = command.ExecuteReader())
                        {
                            if (reader.Read())
                            {
                                return new Echipa(reader.GetInt32(0), reader.GetString(1));
                            }
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Eroare la Delete: {ex.Message}");
            }

            return null;
        }

        public Echipa Update(Echipa entity)
        {
            if (entity == null) throw new ArgumentException("Entitatea nu poate fi null.");
            if (entity.Id == 0) throw new ValidationException("ID-ul nu poate fi zero.");
            if (string.IsNullOrEmpty(entity.echipa_nume)) throw new ValidationException("Numele nu poate fi gol.");

            try
            {
                using (var connection = new NpgsqlConnection(_connectionString))
                {
                    connection.Open();

                    var query = "UPDATE echipa SET nume = @nume WHERE id = @id RETURNING *";
                    using (var command = new NpgsqlCommand(query, connection))
                    {
                        command.Parameters.AddWithValue("@id", entity.Id);
                        command.Parameters.AddWithValue("@nume", entity.echipa_nume);

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
                Console.WriteLine($"Eroare la Update: {ex.Message}");
            }

            return entity;
        }
    }
}
