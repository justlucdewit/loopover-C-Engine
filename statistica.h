#include <stdlib.h>
#include <stdio.h>

typedef struct RecordItem{
	union Value{
		int intVal;
		float floatVal;
	}value;

	char isInt;
} RecordItem;

typedef struct recording{
	RecordItem* records;
	size_t count, capacity;
} recording;

recording emptyRecording(){
	return (recording) { .count = 0, .capacity = 0, .records = NULL };
}

void growRecording(recording* rec){
	if (rec->count >= rec->capacity){
		size_t new_cap = (rec->capacity * 15) / 10 + 1;
		RecordItem* newRecs = realloc(rec->records, new_cap * sizeof(*rec->records));

		rec->capacity = new_cap;
		rec->records = newRecs;
	}
}

void addIntRecord(recording* rec, int value){
	// grow if needed
	growRecording(rec);
	
	// insert new item
	rec->records[rec->count++] = (RecordItem){ .value.intVal = value, .isInt = 1 };
};

void addFloatRecord(recording* rec, float value){
	// grow if needed
	growRecording(rec);
	
	// insert new item
	rec->records[rec->count++] = (RecordItem){ .value.floatVal = value, .isInt = 0 };
};

void listRecording(recording rec){
	for (unsigned int i = 0; i < rec.count; i++){
		if (rec.records[i].isInt){
			printf("%d: %d\n", i, rec.records[i].value.intVal);
		}else{
			printf("%d: %f\n", i, rec.records[i].value.floatVal);
		}
	}
}

double recordingMax(recording rec){
	if (rec.count == 0){
		perror("ERROR: cannot find Max of empty recording");
		exit(1);
	}

	double highest;

	if (rec.records[0].isInt){
		highest = (double)rec.records[0].value.intVal;
	}else{
		highest = (double)rec.records[0].value.floatVal;
	}

	for (unsigned int i = 0; i < rec.count; i++){
		RecordItem item = rec.records[i];
		if (item.isInt){
			if (item.value.intVal > highest)
				highest = (double)item.value.intVal;
		}else{
			if (item.value.floatVal > highest)
				highest = (double)item.value.floatVal;
		}
	}

	return highest;
};


double recordingMin(recording rec){
	if (rec.count == 0){
		perror("ERROR: cannot find Min of empty recording");
		exit(1);
	}

	double lowest;

	if (rec.records[0].isInt){
		lowest = (double)rec.records[0].value.intVal;
	}else{
		lowest = (double)rec.records[0].value.floatVal;
	}

	for (unsigned int i = 0; i < rec.count; i++){
		RecordItem item = rec.records[i];
		if (item.isInt){
			if (item.value.intVal < lowest)
				lowest = (double)item.value.intVal;
		}else{
			if (item.value.floatVal < lowest)
				lowest = (double)item.value.floatVal;
		}
	}

	return lowest;
};

double recordingSum(recording rec){
	double sum;

	for (unsigned int i = 0; i < rec.count; i++){
		RecordItem item = rec.records[i];
		if (item.isInt){
			sum += item.value.intVal;
		}else{
			sum += item.value.floatVal;
		}
	}

	return sum;
};

double recordingMean(recording rec){
	return recordingSum(rec) / rec.count;
};