/*  A class representing a set of points and the format
 * that we will be storing them
 * 
 * 
 * @author Oscar Barney
 */


#ifndef PICKED_POINTS_H
#define PICKED_POINTS_H

#include <QString>
#include <QMap>
#include <QSqlQuery>
#include <QHash>
#include <QMessageBox>

#include "../humandb/meshmodel.h"

//our points
class PickedPoint
{
public:
	PickedPoint(QString _name, vcg::Point3f _point, bool _present, QString _item){
		name = _name;
		point = _point;
		present = _present;
		item = _item;
	}
	
	//name of point
	QString name;  
	
	//if we are using a template and a point we need to label does not exist we can use
	//this flag to indicate the point could not be picked
	bool present;

	//point
	vcg::Point3f point;
	//belong to item
	QString item;
};

class PickedPoints
{
public:
	
	PickedPoints();
	
	~PickedPoints();
	
	//opens a file containing the picked points
	bool open(QString filename);
	
	//save 
	bool save(QString filename, QString dataFileName);

	//save to DB
	bool saveToDB();

	//add a point to the map
	void addPoint(QString name, vcg::Point3f point, bool present, QString item);
	
	std::vector<PickedPoint*> * getPickedPointVector();
	
	//get a vector containing only active points
	std::vector<vcg::Point3f> * getPoint3fVector();
	
	//translate each point using the matrix
	//if the mesh moves you can then translate the points useing this function
	void translatePoints(vcg::Matrix44f &translation);
	
	//get the suggested filename for the points.  will be based on the mesh's filename
	static QString getSuggestedPickedPointsFileName(const MeshModel &meshModel);
	
	//set the template name
	void setTemplateName(QString name);
	
	//get the template name
	const QString & getTemplateName();
		
	//extension of the filetype for Picked Points
	static const QString fileExtension;
	
	//for use with per mesh attributes
	static const std::string Key;
	
private:
	
	//data
	std::vector<PickedPoint*> *pointVector;
	
	//the template that was used to pick these points
	//will be "" if no template was used
	QString templateName;
	
	//Declare Constants
	
	//root name of the xml document
	static const QString rootName;
	
	static const QString documentDataElementName;
	
	static const QString dateTimeElementName;
	
	static const QString date;
	
	static const QString time;
	
	static const QString userElementName;
	
	//the file the points were placed on
	static const QString dataFileElementName;
	
	//the templateName if one was used
	static const QString templateElementName;
	
	//point element's name
	static const QString pointElementName;
	
	//point's name
	static const QString name;
	
	//tells whether the point is active
	//can really indicate whatever you want but is mostly used to indicate
	//whether the point should be used.  a point can be inactive if it is part of a 
	//template and could not be found or if you want to indicate that the value picked
	//is not reliable
	static const QString active;
	
	//point's x coord
	static const QString xCoordinate;
	
	//point's y coord
	static const QString yCoordinate;
	
	//points z coord
	static const QString zCoordinate;
	
	//to indicate whether the point is active
	static const QString True;
	
	//to indicate whether the point is inactive
	static const QString False;

	//to indicate the point belong to a itemName
	static const QString itemName;

	//hash table <itemname, itemnum>
	QHash<QString, QString> item_name_num;
};

#endif