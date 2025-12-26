using Npgsql;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace Laborator13
{
    internal class RepoJucatorActiv : IRepository<int, JucatorActiv>
    {
        private readonly string _connectionString;

        public RepoJucatorActiv(string connectionString)
        {
            _connectionString = connectionString;
        }

        public JucatorActiv FindOne(int id)
        {
            try
            {
                if (id == 0) throw new ArgumentException("ID-ul nu poate fi null sau zero.");

                using (var connection = new NpgsqlConnection(_connectionString))
                {
                    connection.Open();

                    var query = "SELECT * FROM jucatoractiv WHERE id = @Id";
                    using (var command = new NpgsqlCommand(query, connection))
                    {
                        command.Parameters.AddWithValue("@Id", id);

                        using (var reader = command.ExecuteReader())
                        {
                            if (reader.Read())
                            {
                                return new JucatorActiv(reader.GetInt32(0), reader.GetInt32(1), reader.GetInt32(2), reader.GetInt32(3), reader.GetString(4));
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

        public IEnumerable<JucatorActiv> FindAll()
        {
            var jucatoriActiv = new List<JucatorActiv>();

            try
            {
                using (var connection = new NpgsqlConnection(_connectionString))
                {
                    connection.Open();

                    var query = "SELECT * FROM jucatoractiv";
                    using (var command = new NpgsqlCommand(query, connection))
                    {
                        using (var reader = command.ExecuteReader())
                        {
                            while (reader.Read())
                            {
                                jucatoriActiv.Add(new JucatorActiv(reader.GetInt32(0), reader.GetInt32(1), reader.GetInt32(2), reader.GetInt32(3), reader.GetString(4)));
                            }
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Eroare în FindAll: {ex.Message}");
            }

            return jucatoriActiv;
        }

        public JucatorActiv Save(JucatorActiv entity)
        {
            try
            {
                if (entity == null) throw new ArgumentException("Entitatea nu poate fi null.");
                if (entity.Id == 0) throw new ValidationException("ID-ul nu poate fi zero.");
                if (string.IsNullOrEmpty(entity.Tip)) throw new ValidationException("Tipul nu poate fi gol.");
                if (entity.NrPuncte < 0) throw new ValidationException("Numărul de puncte nu poate fi negativ.");

                using (var connection = new NpgsqlConnection(_connectionString))
                {
                    connection.Open();

                    var query = "INSERT INTO jucatoractiv (id_jucator, id_meci, nr_puncte, tip) VALUES (@IdJucator, @IdMeci, @NrPuncte, @Tip)";
                    using (var command = new NpgsqlCommand(query, connection))
                    {
                        command.Parameters.AddWithValue("@IdJucator", entity.IdJucator);
                        command.Parameters.AddWithValue("@IdMeci", entity.IdMeci);
                        command.Parameters.AddWithValue("@NrPuncte", entity.NrPuncte);
                        command.Parameters.AddWithValue("@Tip", entity.Tip);

                        command.ExecuteNonQuery();
                    }
                }

                return null;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Eroare în Save: {ex.Message}");
                return entity;
            }
        }

        public JucatorActiv Delete(int id)
        {
            try
            {
                if (id == 0) throw new ArgumentException("ID-ul nu poate fi null sau zero.");

                using (var connection = new NpgsqlConnection(_connectionString))
                {
                    connection.Open();

                    var query = "DELETE FROM jucatoractiv WHERE id = @Id";
                    using (var command = new NpgsqlCommand(query, connection))
                    {
                        command.Parameters.AddWithValue("@Id", id);

                        int affectedRows = command.ExecuteNonQuery();
                        if (affectedRows > 0)
                        {
                            return new JucatorActiv(id, 0, 0, 0, string.Empty); // Poți modifica acest lucru pentru a reflecta o entitate completă
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

        public JucatorActiv Update(JucatorActiv entity)
        {
            try
            {
                if (entity == null) throw new ArgumentException("Entitatea nu poate fi null.");
                if (entity.Id == 0) throw new ValidationException("ID-ul nu poate fi zero.");
                if (string.IsNullOrEmpty(entity.Tip)) throw new ValidationException("Tipul nu poate fi gol.");
                if (entity.NrPuncte < 0) throw new ValidationException("Numărul de puncte nu poate fi negativ.");

                using (var connection = new NpgsqlConnection(_connectionString))
                {
                    connection.Open();

                    var query = "UPDATE jucatoractiv SET id_jucator = @IdJucator, id_meci = @IdMeci, nr_puncte = @NrPuncte, tip = @Tip WHERE id = @Id";
                    using (var command = new NpgsqlCommand(query, connection))
                    {
                        command.Parameters.AddWithValue("@Id", entity.Id);
                        command.Parameters.AddWithValue("@IdJucator", entity.IdJucator);
                        command.Parameters.AddWithValue("@IdMeci", entity.IdMeci);
                        command.Parameters.AddWithValue("@NrPuncte", entity.NrPuncte);
                        command.Parameters.AddWithValue("@Tip", entity.Tip);

                        command.ExecuteNonQuery();
                    }
                }

                return null;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Eroare în Update: {ex.Message}");
            }

            return entity;
        }
    }
}
