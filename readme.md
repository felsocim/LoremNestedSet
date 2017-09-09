# Lorem Nested Set

Simple console application allowing to generate mock nested set data strcutures for SQL-based databases development and testing purposes. **Lorem Nested Set** generates a mock nested set data strcuture according to optional user preferences and exports it as a SQL script containing appropriate data insertion statements. The latter is fully configurable and can be used to build a mock nested set data structure within an SQL-based database. 

![Nested set database model example](https://image.ibb.co/bU5mta/Nested_Set_Model_Ex.png)

## Getting started

### Prerequisities

The application needs to be built before use. To obtain the appropriate executable you will need to use a C compiler such as GCC compatible with both Linux and Windows operating systems.

#### Linux users

If you are working under Linux, you may have already installed GCC compiler. If not, you can do so by executing the following command in terminal:

```bash
sudo apt-get install build-essential
```

#### Windows users

Windows does not have a native GCC support but you can use a Unix-like environment such as [Cygwin](https://www.cygwin.com) or [MinGW](www.mingw.org) with **gcc** and **make** packages installed.

### Build

Once the GCC compiler installed, you can build an executable using ``make`` command which will use the makefile included to automatically perform all compilation commands. The resulting executable will be saved to bin folder located in the application's root directory.

## Usage

To run Lorem Nested Set from the command line use the following sytax:

```bash
lnt -o "<output SQL script file>" \[-d, -m, -M, -t, -l, -r, -v, -L, -h\]
```
	
The application defaults are set to following values:
* structure depth:					3 levels
* minimum nodes count per level:	1
* maximum nodes count per level:	5
* target SQL table name:			'mock_table'
* left boundary column name:		'left'
* right boundary column name:		'right'
* by default level column is not included in output script

The above parameters can be modified by using available options:

| Option | Descirption |
| ------ | ----------- |
| -o | specifies output script file *(mandatory)* |
| -d | depth of data structure *(number of levels)*
| -m | minimum nodes count per level *(default value: 1)* |
| -M | maximum nodes count per level *(default value: 5)* |
| -t | custom name *(without quotes or \`)* for target SQL table *(default value: 'mock_table')* |
| -l | custom name *(without quotes or \`)* for left boundary column *(default value: 'left')* |
| -r | custom name *(without quotes or \`)* for right boundary column *(default value: 'right')* |
| -v | export also level column with its default name *(not associable with -L option)* |
| -L | custom name *(without quotes or \`)* for level column *(not associable with -v option)* |
| -h | displays this text |

**Example of application execution**

![Example of application execution](https://preview.ibb.co/jMKeDa/LNSEx.png)

**Extract of application output**

``export.sql``

```sql
INSERT INTO mock_table (`left`, `right`, `level`) VALUES (1, 296, 0);
INSERT INTO mock_table (`left`, `right`, `level`) VALUES (2, 43, 1);
INSERT INTO mock_table (`left`, `right`, `level`) VALUES (44, 85, 1);
INSERT INTO mock_table (`left`, `right`, `level`) VALUES (86, 127, 1);
INSERT INTO mock_table (`left`, `right`, `level`) VALUES (128, 169, 1);
INSERT INTO mock_table (`left`, `right`, `level`) VALUES (170, 211, 1);
INSERT INTO mock_table (`left`, `right`, `level`) VALUES (212, 253, 1);
INSERT INTO mock_table (`left`, `right`, `level`) VALUES (254, 295, 1);
INSERT INTO mock_table (`left`, `right`, `level`) VALUES (3, 12, 2);
INSERT INTO mock_table (`left`, `right`, `level`) VALUES (13, 22, 2);
INSERT INTO mock_table (`left`, `right`, `level`) VALUES (23, 32, 2);
INSERT INTO mock_table (`left`, `right`, `level`) VALUES (33, 42, 2);
INSERT INTO mock_table (`left`, `right`, `level`) VALUES (45, 54, 2);
INSERT INTO mock_table (`left`, `right`, `level`) VALUES (55, 64, 2);
INSERT INTO mock_table (`left`, `right`, `level`) VALUES (65, 74, 2);
INSERT INTO mock_table (`left`, `right`, `level`) VALUES (75, 84, 2);
INSERT INTO mock_table (`left`, `right`, `level`) VALUES (87, 96, 2);
INSERT INTO mock_table (`left`, `right`, `level`) VALUES (97, 106, 2);
INSERT INTO mock_table (`left`, `right`, `level`) VALUES (107, 116, 2);
...
```

## Authors

* [**Marek Felsoci**](http://www.marekonline.eu) - *Student* - [University of Strasbourg](https://www.unistra.fr)

## License

**Lorem Nested Set** is licensed under the terms of the [MIT License](https://opensource.org/licenses/MIT).

## Credits

* Nested set database model example image by [Nestedsetmodel.jpg: Sherahmderivative work: 0x24a537r9 (talk) - Nestedsetmodel.jpg, Public Domain](https://commons.wikimedia.org/w/index.php?curid=10979293)
