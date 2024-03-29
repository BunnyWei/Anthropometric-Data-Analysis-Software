/*  A class representing a set of points and the format
 * that we will be storing them
 * 
 * 
 * @author Oscar Barney
 */

#include "pickedPoints.h"

#include <QtGui>
#include <QMap>
#include <QList>

//xml stuff
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNode>

//Define Constants
const QString PickedPoints::fileExtension = ".pp";
const QString PickedPoints::rootName = "PickedPoints";

const QString PickedPoints::documentDataElementName = "DocumentData";
const QString PickedPoints::dateTimeElementName = "DateTime";
const QString PickedPoints::date = "date";
const QString PickedPoints::time = "time";
const QString PickedPoints::userElementName = "User";
const QString PickedPoints::dataFileElementName = "DataFileName";
const QString PickedPoints::templateElementName = "templateName";

const QString PickedPoints::pointElementName = "point";
const QString PickedPoints::name = "name";
const QString PickedPoints::active = "active";
const QString PickedPoints::xCoordinate = "x";
const QString PickedPoints::yCoordinate = "y";
const QString PickedPoints::zCoordinate = "z";
const QString PickedPoints::True = "1";
const QString PickedPoints::False = "0";
const QString PickedPoints::itemName = "itemName";
const std::string PickedPoints::Key = "PickedPoints";


PickedPoints::PickedPoints(){
	pointVector = new std::vector<PickedPoint *>();
	QSqlQuery query("select itemname, itemnumber from item");
	query.exec();
	QString itemname, itemnumber;
	while (query.next())
	{
		itemname = query.value(0).toString();
		itemnumber = query.value(1).toString();

		item_name_num.insert(itemname, itemnumber);
	}
}

PickedPoints::~PickedPoints(){
	delete pointVector;
}

bool PickedPoints::open(QString filename){
	QDomDocument doc;
	pointVector->clear();
	
	QFile file(filename);
	
	QString errorMessage;
	if (file.open(QIODevice::ReadOnly) && doc.setContent(&file, &errorMessage)) 
	{
		file.close();
		QDomElement root = doc.documentElement();
		if (root.nodeName() == rootName) 
	    {
			qDebug() << "About to read a " << rootName << " xml document";
			
			templateName = "";
			QDomElement dataElement = root.firstChildElement(documentDataElementName);
			if(!dataElement.isNull()){
				QDomElement templateElement = dataElement.firstChildElement(templateElementName);
				if(!templateElement.isNull()) templateName = templateElement.attribute(name);
			} 
			
			qDebug() << "Template loaded: " << templateName;
			
			for(QDomElement element = root.firstChildElement(pointElementName);
				!element.isNull();
				element = element.nextSiblingElement(pointElementName))
			{
				QString pointName = element.attribute(name);
				qDebug() << "Reading point with name " << pointName;
				
				QString x = element.attribute(xCoordinate);
				QString y = element.attribute(yCoordinate);
				QString z = element.attribute(zCoordinate);
				
				vcg::Point3f point(x.toFloat(), y.toFloat(), z.toFloat());
				
				QString presentString = element.attribute(active);
				bool present = true;
				if(False == presentString) present = false;
				QString item = element.attribute(itemName);;
				addPoint(pointName, point, present, item);
				
			}
	    } else {
	    	//file is of unknown type
	    	qDebug() << "Failed, tried to read a " << rootName << " xml document";
	    	return false;
	    }
		
	} else {
		// problem opening the file
		qDebug() << "problem reading from the file, setContent error: " <<  errorMessage;
		return false;
	}
	return true;
}



bool PickedPoints::save(QString filename, QString dataFileName)
{
	QDomDocument doc(rootName);
	QDomElement root = doc.createElement(rootName);
	doc.appendChild(root);
	
	//put in the template name
	QDomElement dataTag = doc.createElement(documentDataElementName);
	root.appendChild(dataTag);
	
	//put in the template name
	QDomElement data = doc.createElement(dateTimeElementName);
	data.setAttribute(date, QDate::currentDate().toString(Qt::ISODate));
	data.setAttribute(time, QTime::currentTime().toString(Qt::ISODate));
	dataTag.appendChild(data);

	char *user = 0;
	user = getenv("USERNAME"); //windows xp/vista
	if(NULL == user) user = getenv("LOGNAME"); //linux and maybe apple? 
	if(NULL != user)
	{
		data = doc.createElement(userElementName);
		data.setAttribute(name, QString(user));
		dataTag.appendChild(data);
	}
	
	data = doc.createElement(dataFileElementName);
	data.setAttribute(name, dataFileName);
	dataTag.appendChild(data);
	
	data = doc.createElement(templateElementName);
	data.setAttribute(name, templateName);
	dataTag.appendChild(data);
		
	//create an element for each point
	for (unsigned int i = 0; i < pointVector->size(); ++i) {
		PickedPoint *pickedPoint = pointVector->at(i);
		
		QDomElement tag = doc.createElement(pointElementName);
		
		vcg::Point3f point = pickedPoint->point;
		
		tag.setAttribute(xCoordinate, point[0] );
		tag.setAttribute(yCoordinate, point[1] );
		tag.setAttribute(zCoordinate, point[2] );
		
		//if the point is not present indicate this
		if(pickedPoint->present)
			tag.setAttribute(active, QString(True));
		else 
			tag.setAttribute(active, QString(False));
		
		tag.setAttribute(name,  pickedPoint->name);
		tag.setAttribute(itemName,  pickedPoint->item);
		//append the element to the root
		root.appendChild(tag);
	}
	
	//create a file and write the data
	QFile file(filename);
	file.open(QIODevice::WriteOnly);
	QTextStream qstream(&file);
	doc.save(qstream,1);
	file.close();
	return true;	 
}

bool PickedPoints::saveToDB()
{
	QSqlQuery query;
	QString sql = "insert into points(name, x, y, z, active, itemnum, itemname) values ";
	for (unsigned int i = 0; i < pointVector->size(); ++i) 
	{
		PickedPoint *pickedPoint = pointVector->at(i);
		
		vcg::Point3f point = pickedPoint->point;
		sql += "('" + pickedPoint->name + "', ";
		sql += QString("%1, ").arg(point[0]);
		sql += QString("%1, ").arg(point[1]);
		sql += QString("%1, ").arg(point[2]);
		if(pickedPoint->present)
			sql += QString("%1, ").arg(1);
		else 
			sql += QString("%1, ").arg(0);

		QString itemnum = item_name_num[pickedPoint->item];
		sql += "'" + itemnum + "', ";
		sql += "'" + pickedPoint->item + "'";

		if (i == pointVector->size() - 1)
			sql += ")";
		else
			sql += "), ";		
	}
	qDebug() << "SQL:" << sql;
	if (query.exec(sql))
	{
		//QMessageBox::warning(this, "提示", "保存成功！", QMessageBox::Ok);
	    return 1;
	}
	else
	{
		//QMessageBox::warning(this, "提示", "保存失败！", QMessageBox::Ok);
		return 0;
	}
}

void PickedPoints::addPoint(QString name, vcg::Point3f point, bool present, QString item){
	assert(pointVector);
		
	PickedPoint *pickedPoint = new PickedPoint(name, point, present, item);
	pointVector->push_back(pickedPoint);
}

std::vector<PickedPoint*> * PickedPoints::getPickedPointVector()
{
	return pointVector;
}

std::vector<vcg::Point3f> * PickedPoints::getPoint3fVector()
{
	std::vector<vcg::Point3f> *points = new std::vector<vcg::Point3f>();
	
	for(unsigned int i = 0; i < pointVector->size(); i++)
	{
		if(pointVector->at(i)->present )
			points->push_back(pointVector->at(i)->point);
	}
	
	return points;
}

void PickedPoints::translatePoints(vcg::Matrix44f &translation)
{
	for(unsigned int i = 0; i < pointVector->size(); i++)
	{
		PickedPoint* temp = pointVector->at(i);
	
		//qDebug() << " point was x" << temp->point[0] << " y " << temp->point[1] << " z " << temp->point[2];
		
		vcg::Point4f inputPoint(temp->point[0], temp->point[1], temp->point[2], 1);
		
		vcg::Point4f resultPoint = translation * inputPoint;
		
		temp->point[0] = resultPoint[0];
		temp->point[1] = resultPoint[1];
		temp->point[2] = resultPoint[2];
		
		//qDebug() << " point is now x" << temp->point[0] << " y " << temp->point[1] << " z " << temp->point[2];
	}
}

QString PickedPoints::getSuggestedPickedPointsFileName(const MeshModel &meshModel){
	QString outputFileName(meshModel.fileName.c_str());
	
	//remove postfix
	outputFileName.truncate(outputFileName.length()-4);
				
	//add new postfix
	outputFileName.append("_picked_points" + fileExtension);
	
	return outputFileName;
}

void PickedPoints::setTemplateName(QString name)
{
	templateName = name;
}

const QString & PickedPoints::getTemplateName()
{
	return templateName;
}
