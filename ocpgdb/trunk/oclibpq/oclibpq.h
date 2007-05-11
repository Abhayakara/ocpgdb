/* vi:set sw=8 ts=8 noet showmode ai: */

/* Python */
#include <Python.h>
#include <structmember.h>

/* PostgreSQL */
#include <libpq-fe.h>
#include <libpq/libpq-fs.h>

/* Python 2.3 compatibility - copied from Python 2.5 source */
#ifndef Py_VISIT
#define Py_VISIT(op)							\
        do { 								\
                if (op) {						\
                        int vret = visit((PyObject *)(op), arg);	\
                        if (vret)					\
                                return vret;				\
                }							\
        } while (0)
#endif
#ifndef Py_CLEAR
#define Py_CLEAR(op)				\
        do {                            	\
                if (op) {			\
                        PyObject *tmp = (PyObject *)(op);	\
                        (op) = NULL;		\
                        Py_DECREF(tmp);		\
                }				\
        } while (0)
#endif
#if (PY_VERSION_HEX < 0x02050000)
typedef int Py_ssize_t;
#endif

#define MODULE_NAME "oclibpq"

enum result_type {
	RESULT_DQL,
	RESULT_DDL,
	RESULT_DML,
	RESULT_EMPTY,
};

typedef struct {
	PyStringObject	str;
} PyPgBytea;

typedef struct {
	PyObject_HEAD
	PGconn		*connection;
	PyObject 	*conninfo;
	PyObject 	*notices;
} PyPgConnection;

typedef struct {
	PyObject_HEAD
	PyPgConnection	*connection;
	PGresult	*result;
	enum result_type result_type;
	int		 row_number;
	int		 row_count;
	PyObject 	*columns;
} PyPgResult;

typedef struct {
	PyObject_HEAD
	PyObject *format;	
	PyObject *modifier;	
	PyObject *name;	
	PyObject *type;	
	PyObject *value;	
} PyPgCell;

extern PyObject *PqErr_Warning;
extern PyObject *PqErr_Error;
extern PyObject *PqErr_InterfaceError;
extern PyObject *PqErr_DatabaseError;
extern PyObject *PqErr_DataError;
extern PyObject *PqErr_OperationalError;
extern PyObject *PqErr_IntegrityError;
extern PyObject *PqErr_InternalError;
extern PyObject *PqErr_ProgrammingError;
extern PyObject *PqErr_NotSupportedError;


/* pqconnection.c */
extern void pg_connection_init(PyObject *module);
#define PyPgConnection_Check(op) ((op)->ob_type == &PyPgConnection_Type)

/* pqresult.c */
extern void pg_result_init(PyObject *module);
extern PyObject *PyPgResult_New(PyPgConnection *connection, PGresult *result);
#define PyPgResult_Check(op) ((op)->ob_type == &PyPgResult_Type)

/* pqexception.c */
extern void pg_exception_init(PyObject *module);

/* pqcell.c */
extern PyObject *PyPgCell_New(PGresult *, int);
extern PyObject *PyPgCell_FromCell(PyPgCell *cell, PyObject *value);
extern void pg_cell_init(PyObject *module);
extern int PyPgCell_Check(PyObject *);

/* bytea.c */
extern void pg_bytea_init(PyObject *module);
extern int PyPgBytea_Check(PyObject *);
