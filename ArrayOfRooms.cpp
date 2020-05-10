#include "ArrayOfRooms.h"

/*bool ArrayOfRooms::contains(int r, DateTime f, DateTime t)
{
    for (int i = 0; i < 300; i++)
    {
        if (rooms[i].getNumber() == r &&
            ((rooms[i].getDateFrom() <= f && rooms[i].getDateTo() >= f) &&
                (rooms[i].getDateFrom() <= t && rooms[i].getDateTo() >= t)))
        {
            return true;
        }
    }
    return false;
}*/

Room& ArrayOfRooms::operator[](int i)
{
    return rooms[i];
}

void ArrayOfRooms::add(int r, DateTime f, DateTime t, string n, int g)
{
    bool isBetween = ((rooms[r - 1].getDateFrom() <= f && rooms[r - 1].getDateTo() >= f) &&
        (rooms[r - 1].getDateFrom() <= t && rooms[r - 1].getDateTo() >= t));
    
    bool isOutside = ((rooms[r - 1].getDateFrom() >= f && rooms[r - 1].getDateTo() >= f) &&
        (rooms[r - 1].getDateFrom() <= t && rooms[r - 1].getDateTo() <= t));

    bool isBetweenUn = ((f <= unavailable[r].getFrom() && t >= unavailable[r].getFrom()) &&
        (f <= unavailable[r].getTo() && t >= unavailable[r].getTo()));

    bool isOutsideUn = ((f >= unavailable[r].getFrom() && t >= unavailable[r].getFrom()) &&
        (f <= unavailable[r].getTo() && t <= unavailable[r].getTo()));

    if (unavailable[r].getStatus() == "unavailable" && (isBetweenUn || isOutsideUn))
    {
        cout << "This room is unavailable from " << unavailable[r].getFrom() << " to " 
            << unavailable[r].getTo() << " due to the fact it's" << unavailable[r].getNote() 
            << ". Please try to rent a room in another date." << endl;
    }
    else
    {
        if (status[r - 1] == "checkedin" && (isBetween || isOutside))
        {
            cout << "You can't check in this room. It is already rented!" << endl;
        }
        else
        {
            for (int i = 0; i < sizeOfRooms; i++)
            {
                if (i + 1 == r)
                {
                    rooms[i].changeSettings(f, t, n, g);
                    status[i] = "checkedin";
                    daysInRoom[i] += (t - f);
                    cout << rooms[i];
                }
            }
        }
    }
    //if (!contains(r, f, t))
    //{
        //rooms.push_back(newRoom);
    //}
    //else
    //{
        //cout << "This room is already rented." << endl;
    //}
}

void ArrayOfRooms::check(DateTime date, string today)
{

    for (int i = 0; i < sizeOfRooms; i++)
    {
        if (date >= rooms[i].getDateFrom() && date <= rooms[i].getDateTo())
        {
            if (today == "today")
            {
                cout << "Room number " << rooms[i].getNumber() << " is not free today" << endl;
            }
            else
            {
                cout << "Room number " << rooms[i].getNumber() << " is rented from " << rooms[i].getDateFrom()
                     << " to " << rooms[i].getDateTo() << endl;
            }
        }
        else
        {
            if (today == "today")
            {
                cout << "Room number " << rooms[i].getNumber() << " is free today" << endl;
            }
            else
            {
                cout << "Room number " << rooms[i].getNumber() << " is free on this date" << endl;
            }
        }
    }
}

void ArrayOfRooms::release(int number)
{
    int counter = 0;

    for (int i = 0; i < sizeOfRooms; i++)
    {
        if (rooms[i].getNumber() == number && status[i] == "checkedin")
        {
            rooms[i].changeSettings(DateTime(), DateTime(), "", 0);
            cout << "Room succesfully checked out!" << endl;
            status[i] = "checkedout";
        }
        else if (rooms[i].getNumber() == number && status[i] == "checkedout")
        {
            cout << "The room you want to check out is free!" << endl;
        }
        else
        {
            counter++;
        }
    }

    if (counter == sizeOfRooms) cout << "The room you want to check out is free!" << endl;
}

void ArrayOfRooms::list(DateTime dateFrom, DateTime dateTo)
{
    for (int i = 0; i < sizeOfRooms; i++)
    {
        if ((rooms[i].getDateFrom() <= dateFrom && rooms[i].getDateTo() >= dateFrom) &&
            (rooms[i].getDateFrom() <= dateTo && rooms[i].getDateTo() >= dateTo))
        {
            cout << dateTo - dateFrom << endl;
        }
        else if((rooms[i].getDateFrom() >= dateFrom && rooms[i].getDateTo() >= dateFrom)&&
            (rooms[i].getDateFrom() <= dateTo && rooms[i].getDateTo() <= dateTo))
        {
            cout << daysInRoom[i] << endl;
        }
        else
        {
            cout << 0 << endl;
        }
    }
}

void ArrayOfRooms::findRoom(int number, DateTime dateFrom, DateTime dateTo)
{
    bool isBetween, isOutside;

    for (int i = 0; i < sizeOfRooms; i++)
    {
        bool isBetween = ((rooms[i].getDateFrom() <= dateFrom && rooms[i].getDateTo() >= dateFrom) &&
            (rooms[i].getDateFrom() <= dateTo && rooms[i].getDateTo() >= dateTo));

        bool isOutside = ((rooms[i].getDateFrom() >= dateFrom && rooms[i].getDateTo() >= dateFrom) &&
            (rooms[i].getDateFrom() <= dateTo && rooms[i].getDateTo() <= dateTo));

        if (rooms[i].getGuests() == number && (isBetween || isOutside) && status[i] != "checkedin")
        { 
            cout << "Room number " << rooms[i].getNumber() << " is free with " << number << "beds." << endl;
        }
        else
        {
            if (rooms[i].getGuests() != number)
            {
                cout << "Room number " << rooms[i].getNumber() << " hasn't got that much beds!" << endl;
            }
            else if (status[i] == "checkedin" && (isBetween || isOutside))
            {
                cout << "Room number " << rooms[i].getNumber() << " is already rented from " 
                     << rooms[i].getDateFrom() << " to " << rooms[i].getDateTo() << endl;
            }  
            else
            {
                cout << "On this date room number " << rooms[i].getNumber() << " is free." << endl;
            }
        }
    }
}

void ArrayOfRooms::findVIPRoom(int number, DateTime dateFrom, DateTime dateTo)
{

}

void ArrayOfRooms::freeze(int _number, DateTime _dateFrom, DateTime _dateTo, string _note)
{
    unavailable[_number].change(_number, _dateFrom, _dateTo, _note);
}

void ArrayOfRooms::print()
{
    for (int i = 0; i < sizeOfRooms; i++)
    {
        cout << rooms[i];
    }
}

ostream& operator << (ostream& output, const ArrayOfRooms& rooms)
{
    for (int i = 0; i < sizeOfRooms; i++)
    {
        cout << rooms.rooms[i];
    }
    return output;
}