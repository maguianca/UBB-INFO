package com.example.taximetrie.validator;

public interface Validator<T> {
    void validate(T entity) throws ValidationException;
}