package com.marvellous.MarvellousFullStack.Service;

import com.marvellous.MarvellousFullStack.Entity.BatchEntry;
import com.marvellous.MarvellousFullStack.Repository.BatchEntryRepositry;
import org.bson.types.ObjectId;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.List;
import java.util.Optional;

@Component
public class BatchEntryService
{
    @Autowired
    private BatchEntryRepositry batchEntryRepositry;

    // C : Create  POST
    public void saveEntry(BatchEntry batchEntry)
    {
        batchEntryRepositry.save(batchEntry);
    }

    // R : Read GET
    public List<BatchEntry>getAll()
    {
        return batchEntryRepositry.findAll();
    }

    // R : Read GET
    public Optional<BatchEntry> findById(ObjectId id)
    {
        return batchEntryRepositry.findById(id);
    }

    // D : Delete DELETE
    public void deleteById(ObjectId id)
    {
        batchEntryRepositry.deleteById(id);
    }
}
