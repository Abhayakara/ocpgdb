**ocpgdb** is a Python DB-API 2 (aka [pep-0249](http://www.python.org/dev/peps/pep-0249/)) adapter for PostgreSQL. The code is simple, modular and extensible, with most of the intelligence implemented in Python with only a small C wrapper around libpq. The module is used in several production systems, and while there is little documentation at this stage, most things work as described in [pep-0249](http://www.python.org/dev/peps/pep-0249/).

Unlike most Python PG adapters, this module uses the newer binary PG protocol 3 - in many cases this protocol is faster and safer, although the protocol is less forgiving of implicit type-casting. As an example, other adapters will accept:
```
curs.execute('SELECT * FROM foo WHERE bah > %s', '2006-1-1')
```
whereas protocol 3 requires:
```
curs.execute('SELECT * FROM foo WHERE bah > %s', datetime.datetime(2006,1,1))
```
or an explicit cast:
```
curs.execute('SELECT * FROM foo WHERE bah > %s::timestamp', '2006-1-1')
```

The module requires Python 2.3 or newer, and PostgreSQL 8.1 or newer. If [mx.DateTime](http://www.egenix.com/products/python/mxBase/mxDateTime/) is available, use\_mx\_datetime=True can be passed to the connect() function to enable support.
To install, unpack the tar file, and as root run:
```
python setup.py install
```

The **ocpgdb** module's development was sponsored by [Object Craft](http://www.object-craft.com.au/).