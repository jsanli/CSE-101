
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include "Dictionary.h"
#include "Enrollment.h"
	

// create global dictionaries
dictionary CourseDict;
dictionary StudentDict;

// -------------------------------------------
// adds *e to the CourseDict.
// Checks if *e already exists, if so print error message
// and don't update the dictionary.  Else update dictionary.
// -------------------------------------------
void addCourse(course_element *e) {
    // check if course already exists in dictionary else print message

    // if not, insert to course dict
    if (find(&CourseDict, e->key) != NULL) {
        printf("%s\n", "course already exists");
    } else {
        insert(&CourseDict, (element *) (e));
        print(&CourseDict);
    }
}

// -------------------------------------------
// deletes course whose ID/key is c_key from the CourseDict.
// This should check if the course to be deleted exists.
// If not, just print an error message: "Course does not exist."
// If the course exists, then this will also drop students who
// are currently enrolled in the course and then remove course
// from course dict
// -------------------------------------------
void delCourse(char *c_key) {
    // check if course is in the dict - if not, print error and return

    // get course info from the corresponding node
    // loop over the list of students enrolled in course and drop them
    // NOTE: be careful because you are looping over the same list -
    // you are removing elements from

    // delete course with given key from dictionary
    if (find(&CourseDict, c_key) == NULL) {
        fprintf(stderr, "%s\n", "error");
        return;
    } else {
        node_t course = *find(&CourseDict, c_key);
        course_element course_e = *(course_element *) (&course);
        for (int x = 0; x < course_e.value->num_students; x++) {
            drop(course_e.value->list->key, c_key);
            course_e.value->list = course_e.value->list->next;
        }
        course_e.value->list = NULL;
        delete (&CourseDict, c_key);
    }
    return;
}

// -------------------------------------------
// enrolls student into course. params are s_key and c_key
// Need to check for: existence of course, and if student
// is already enrolled in the course.  Also check if course
// is full or if student has reached max number of courses.
// If there's any error, print a message and don't enroll
// the student.  If there's no errors, update both dictionaries.
// -------------------------------------------
void enroll(char *s_key, char *c_key) {
    // declare vars for nodes coressponding to course entry and student entry
    // in respective dictionaries
    student_element student = *(student_element *) calloc(1, sizeof(student_element));
    memcpy(student.key, s_key, 5);
    course_element course = *(course_element *) calloc(1, sizeof(course_element));
    memcpy(course.key, c_key, 5);
    student.value = (student_value *) (newNode('s'));
    course.value = (course_value *) (newNode('c'));
    student.value->num_courses = 0;
    course.value->num_students = 0;

    // decalare vars for course info and student info corresponding to
    // the value fields of each node/element
    // initialize student info to NULL

    // declare course and student node corresponding to list of courses
    // in a student's node and students in a course's node
    node_t c_node = *(node_t *) calloc(1, sizeof(node_t));
    node_t s_node = *(node_t *) calloc(1, sizeof(node_t));
    memcpy(s_node.key, s_key, 5);
    memcpy(c_node.key, c_key, 5);
    s_node.value = student.value;
    c_node.value = course.value;

    // fetch course and student corresponding to keys from respective dicts
    // initialize vars depending on whether student/course with given key
    // is in the dictionary

    if (find(&CourseDict, c_key) == NULL) {
        fprintf(stderr, "%s\n", "error");
        return;
    }
    if (find(&StudentDict, s_key) == NULL) {
        insert(&StudentDict, (element *) (&student));
        insertList(&student.value->list, &c_node);
    }
    course_element course_e = *(course_element *) (find(&CourseDict, c_key));
    student_element student_e = *(student_element *) (find(&StudentDict, s_key));
    if (findList(course_e.value->list, s_key) != NULL) {
        printf("%s\n", "Student Already in Course");
        return;
    }
    if (student_e.value->num_courses == 2) {
        printf("%s\n", "Student is Already Enrolled in Two Courses");
    }
    if (course_e.value->capacity == course_e.value->num_students) {
        printf("%s\n", "Course is Full");
    } else {
        insertList(&course_e.value->list, &s_node);
        insertList(&student_e.value->list, &c_node);
        course_e.value->num_students++;
    }

    // if course doens't exist, print error and return

    // if student does not exist, insert student to student dict

    // instantiate a 'student_element' pointer struct and set the fields
    // HINT: you can copy the s_key to the key field of student_element
    // using memcpy
    // HINT: you will use the 'newNode' function to instantiate a struct for
    // the value field of the element. See newNode implementation in Enrollment.h
    // the 'value' field of student_element is itself a struct with two fields
    // initialize those fields accordingly
    // insert student element in the corresponding dictionary
    // HINT: you will need to cast the student element as (element*). See Dictionary.h
    // HINT: after you insert student element into student dict, assign the value of that
    // (newly inserted node) to the student info that you initialized to NULL in the beginning

    // check if student is enrolled in the course. If so, print message and return
    // HINT: navigate to the (student) list of the course

    // see if course is full

    // if not, add student to the list (of students) in the course
    // HINT: instantiate a new node and assign it to the node corresp.
    // to student in course's list - initialize the node's fields and
    // insert it into the course's list of students enrolled in it
    // and update the course value fields

    // if student already enrolled in '2' courses, print message and return

    // otherwise, add node to the list of student's enrolled courses
    // HINT: again, instantiate a node (this will be the node of a course
    // in a student's list) and intialize the fields of that node
}

// -------------------------------------------
// drops a student from course. params are s_key and c_key
// Need to check for: existence of course, and if student
// is enrolled in the course.  If any error is encountered,
// print an error message.
// If there are no errors, update both dictionaries.
// -------------------------------------------
void drop(char *s_key, char *c_key) {
    // fetch nodes corresponding to student and course from
    // respective dicts having the given keys

    // if found no such student or course, print message and return

    // see if student is enrolled in the course

    // delete course from student list

    // delete student from course list

    // update counter fields
    if (find(&CourseDict, c_key) == NULL) {
        printf("%s\n", "Course Doesn't Exist");
        return;
    }
    if (find(&StudentDict, s_key) == NULL) {
        printf("%s\n", "Student Doesn't Exist");
        return;
    }
    course_element course_e = *(course_element *) (find(&CourseDict, c_key));
    student_element student_e = *(student_element *) (find(&StudentDict, s_key));
    if (findList(student_e.value->list, c_key) != NULL) {
        node_t *iterator = course_e.value->list;
        for (int x = 0; x < course_e.value->num_students; x++) {
            if (iterator->key == s_key) {
                deleteList(&course_e.value->list, iterator);
                iterator = iterator->next;
            }
        }
        iterator = course_e.value->list;
        for (int x = 0; x < student_e.value->num_courses; x++) {
            if (iterator->key == c_key) {
                deleteList(&course_e.value->list, iterator);
                iterator = iterator->next;
            }
        }
    }
}

// -------------------------------------------
// prints the StudentDict.
// -------------------------------------------
void printStudents() {
    printf("Students:\n");
    print(&StudentDict);
}

// -------------------------------------------
// prints the CourseDict.
// -------------------------------------------
void printCourses() {
    printf("Courses:\n");
    print(&CourseDict);
}

// -------------------------------------------
// Don't edit the code below.  This is the driver code to test
// your implementation.
// -------------------------------------------
int main() {
    char line[100];
    char *command;
    int done = 0;

    course_element *ce;
    //        student_element *se;

    char *course_key;
    char *student_key;

    // initialize dictionaries
    create(&CourseDict, 20);
    create(&StudentDict, 20);

    // process input
    while (!done) {
        // read an entire line as a string
        fgets(line, 100, stdin);

        // pulls command code, assume comma or tab separated
        command = strtok(line, " \t");

        if (strcmp(command, "ex") == 0) {
            printf("Exited Program\n");
            done = 1;
        } else if (strcmp(command, "ac") == 0) // add a new course
        {
            // printf("ac\n");

            // Parse and package rest of line into a course_element
            ce = (course_element *) malloc(sizeof(course_element));
            course_key = strtok(NULL, " ");
            printf("Adding course: %s\n", course_key);
            memcpy((*ce).key, course_key, 5);
            ce->value = (void *) newNode('c');
            ce->value->capacity = atoi(strtok(NULL, " "));
            ce->value->num_students = 0;
            ce->value->list = NULL;
            addCourse(ce);
        } else if (strcmp(command, "dc") == 0) // delete a course
        {
            course_key = strtok(NULL, " ");
            delCourse(course_key);
            printf("Delete Course Complete\n");
        } else if (strcmp(command, "en") == 0) // enroll a student
        {
            // printf("en\n");

            // Parse and package rest of line into a course_element
            student_key = strtok(NULL, " ");
            course_key = strtok(NULL, " ");
            printf("Enrolling student: %s into course: %s\n", student_key, course_key);
            enroll(student_key, course_key);
        } else if (strcmp(command, "dr") == 0) // drop a student
        {
            student_key = strtok(NULL, " ");
            course_key = strtok(NULL, " ");
            printf("Dropping student: %s from course: %s\n", student_key, course_key);
            drop(student_key, course_key);
        } else if (strcmp(command, "ps") == 0) // print students
            printStudents();
        else if (strcmp(command, "pc") == 0) // print courses
            printCourses();
        else
            printf("Unrecognized command: %2s\n", command);
    }

    return 0;
}
