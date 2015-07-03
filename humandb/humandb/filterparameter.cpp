/**************************************************************
** 描 述: 实现的是对应meshLab模块下filterparameter.h中类FilterParameter
和类FiliParameterSet中的函数。函数主要是对于paramList中的参数的操作。
****************************************************************/

#include <QtCore>
#include <QMap>
#include <QPair>
#include <QAction>
#include <vcg/math/matrix44.h>
#include "filterparameter.h"

using namespace vcg;

//下面小模块中函数主要是用于参数列表中判断参数是否存在、参数匹配、参数查找和删除参数。
//判断paramList中是否有对应name的parameter,iterator是迭代器。
bool FilterParameterSet::hasParameter(QString name) 
{
	QList<FilterParameter>::iterator fpli;
	for(fpli=paramList.begin();fpli!=paramList.end();++fpli)
		if((*fpli).fieldName==name)
				return true;
				
	return false;
}
//根据name返回paramList中相应的param
FilterParameter *FilterParameterSet::findParameter(QString name)
{
	QList<FilterParameter>::iterator fpli;
	for(fpli=paramList.begin();fpli!=paramList.end();++fpli)
		if((*fpli).fieldName==name)
				return &*fpli;
		
	qDebug("FilterParameter Warning: Unable to find a parameter with name '%s',\n"
				 "      Please check types and names of the parameter in the calling filter",qPrintable(name));
	return 0;
}
//根据name返回paramList中相应的param
const FilterParameter *FilterParameterSet::findParameter(QString name) const
{
	QList<FilterParameter>::const_iterator fpli;
	for(fpli=paramList.begin();fpli!=paramList.end();++fpli)
		if((*fpli).fieldName==name)
				return &*fpli;
		
	qDebug("FilterParameter Warning: Unable to find a parameter with name '%s',\n"
				 "      Please check types and names of the parameter in the calling filter",qPrintable(name));
	return 0;
}
//根据name移除相应参数
void FilterParameterSet::removeParameter(QString name){
	paramList.removeAll(*findParameter(name));
}
//判断paramList中是否有PARDYNFLOAT类型，若有，获取相应参数mask
int FilterParameterSet::getDynamicFloatMask()
{
	int maskFound=0;
		QList<FilterParameter>::const_iterator fpli;
	for(fpli=paramList.begin();fpli!=paramList.end();++fpli)
		if((*fpli).fieldType==FilterParameter::PARDYNFLOAT)
			maskFound |= (*fpli).mask;
	
	return maskFound;
}

//--------------------------------------

//对bool类型参数的操作
//增加一个bool值的参数到参数列表
void FilterParameterSet::addBool (QString name, bool defaultVal, QString desc, QString tooltip)
{
	assert(!hasParameter(desc));
	FilterParameter p(name,desc,tooltip);
	//fieldVal是QVariant类型的，QVariant可以实例化各种类型变量
  p.fieldVal=defaultVal;
  //fieldType是参数类型，int值。PARBOOL是ParType的枚举变量
	p.fieldType=FilterParameter::PARBOOL;
	paramList.push_back(p);	 
}

//设置bool参数的值
void FilterParameterSet::setBool(QString name, bool newVal)
{
	FilterParameter *p=findParameter(name);
	assert(p);
	p->fieldVal=QVariant(newVal);
}

bool FilterParameterSet::getBool(QString name) const
{
	const FilterParameter *p=findParameter(name);
	assert(p);
	assert(p->fieldType == FilterParameter::PARBOOL);
	//返回一个bool类型变量，如果参数是bool型
	return p->fieldVal.toBool();
}

//--------------------------------------

//对int类型参数的操作
//增加一个int值的参数到参数列表
void FilterParameterSet::addInt(QString name, int       defaultVal, QString desc, QString tooltip)
{
	assert(!hasParameter(desc));
	FilterParameter p(name,desc,tooltip);
  p.fieldVal=defaultVal;
	p.fieldType=FilterParameter::PARINT;
	paramList.push_back(p);		
}
//设置int参数的值
int	 FilterParameterSet::getInt(QString name) const
{
	const FilterParameter *p=findParameter(name);
	assert(p);
	assert(p->fieldType == FilterParameter::PARINT);
	return p->fieldVal.toInt();
}
//返回int类型参数的值
void FilterParameterSet::setInt(QString name, int newVal)
{
	FilterParameter *p=findParameter(name);
	assert(p);
	assert(p->fieldType == FilterParameter::PARINT);
	p->fieldVal=QVariant(newVal);	
}

//--------------------------------------

//对float类型参数的操作
void  FilterParameterSet::addFloat(QString name, float defaultVal, QString desc, QString tooltip)
{
	assert(!hasParameter(desc));
	FilterParameter p(name,desc,tooltip);
  p.fieldVal=defaultVal;
	p.fieldType=FilterParameter::PARFLOAT;
	paramList.push_back(p);		
}
float FilterParameterSet::getFloat(QString name) const
{
	const FilterParameter *p=findParameter(name);
	assert(p);
	assert(p->fieldType == FilterParameter::PARFLOAT);
	return float(p->fieldVal.toDouble());
}
void  FilterParameterSet::setFloat(QString name, float newVal)
{
	FilterParameter *p=findParameter(name);
	assert(p);
	assert(p->fieldType == FilterParameter::PARFLOAT);
	p->fieldVal=QVariant(double(newVal));	
}

//--------------------------------------

//对color类型参数的操作
void  FilterParameterSet::addColor(QString name, QColor defaultVal, QString desc, QString tooltip)
{
	assert(!hasParameter(desc));
	FilterParameter p(name,desc,tooltip);
  p.fieldVal=defaultVal.rgb(); // it is converted to an unsigned int
	p.fieldType=FilterParameter::PARCOLOR;
	paramList.push_back(p);		
}

Color4b FilterParameterSet::getColor4b(QString name) const
{
	QColor c=getColor(name);
	return Color4b(c.red(),c.green(),c.blue(),255);
}

QColor FilterParameterSet::getColor(QString name) const
{
	const FilterParameter *p=findParameter(name);
	assert(p);
	assert(p->fieldType == FilterParameter::PARCOLOR);
	return QColor(QRgb(p->fieldVal.toUInt()));
}

void  FilterParameterSet::setColor(QString name, QColor newVal)
{
	FilterParameter *p=findParameter(name);
	assert(p);
	assert(p->fieldType == FilterParameter::PARCOLOR);
	p->fieldVal=QVariant(newVal.rgb());	
}

//--------------------------------------
//对string类型参数的操作
void FilterParameterSet::addString   (QString name, QString   defaultVal, QString desc, QString tooltip)
{
	assert(!hasParameter(desc));
	FilterParameter p(name,desc,tooltip);
  p.fieldVal=defaultVal; 
	p.fieldType=FilterParameter::PARSTRING;
	paramList.push_back(p);		
}
QString FilterParameterSet::getString(QString name) const
{
	const FilterParameter *p=findParameter(name);
	assert(p);
	assert(p->fieldType == FilterParameter::PARSTRING);
	return p->fieldVal.toString();
}
void FilterParameterSet::setString(QString name, QString newVal)
{
	FilterParameter *p=findParameter(name);
	assert(p);
	assert(p->fieldType == FilterParameter::PARSTRING);
	p->fieldVal=QVariant(newVal);	
}

//--------------------------------------

//对matrix类型参数的操作
Matrix44f		FilterParameterSet::getMatrix44(QString name) const
{
	const FilterParameter *p=findParameter(name);

	assert(p);
	assert(p->fieldType==FilterParameter::PARMATRIX);
	assert(p->fieldVal.type()==QVariant::List);

	Matrix44f matrix;
	QList<QVariant> matrixVals = p->fieldVal.toList();
	assert(matrixVals.size()==16);
	for(int i=0;i<16;++i)
		matrix.V()[i]=matrixVals[i].toDouble();
			return matrix;
}
void FilterParameterSet::addMatrix44 (QString name, Matrix44f defaultVal, QString desc, QString tooltip)
{
	assert(!hasParameter(desc));
	FilterParameter p(name,desc,tooltip);
 
	QList<QVariant> matrixVals;
    for(int i=0;i<16;++i)
        matrixVals.append(defaultVal.V()[i]);
	p.fieldVal=matrixVals;
	p.fieldType=FilterParameter::PARMATRIX;
	paramList.push_back(p);		
}


void FilterParameterSet::setMatrix44(QString , Matrix44f )
{
	assert(0);
}

//--------------------------------------
//对point3f类型参数的操作
Point3f		FilterParameterSet::getPoint3f(QString name) const
{
	const FilterParameter *p=findParameter(name);
	
	assert(p);
	assert(p->fieldType==FilterParameter::PARPOINT3F);
	assert(p->fieldVal.type()==QVariant::List);
	
	Point3f point;
	QList<QVariant> pointVals = p->fieldVal.toList();
	assert(pointVals.size()==3);
	for(int i=0;i<3;++i)
		point[i]=pointVals[i].toDouble();
	return point;
}
void FilterParameterSet::addPoint3f (QString name, Point3f defaultVal, QString desc, QString tooltip)
{
	assert(!hasParameter(desc));
	FilterParameter p(name,desc,tooltip);
	
	QList<QVariant> pointVals;
	for(int i=0;i<3;++i)
		pointVals.append(defaultVal[i]);
	p.fieldVal=pointVals;
	p.fieldType=FilterParameter::PARPOINT3F;
	paramList.push_back(p);		
}
void  FilterParameterSet::setPoint3f(QString name, Point3f newVal)
{
	FilterParameter *p=findParameter(name);
	assert(p);
	assert(p->fieldType == FilterParameter::PARPOINT3F);
	QList<QVariant> pointVals;
	for(int i=0;i<3;++i)
		pointVals.append(newVal[i]);
	p->fieldVal=pointVals;
}
//--------------------------------------
//对AbsPerc类型参数的操作
void FilterParameterSet::addAbsPerc (QString name, float defaultVal, float minVal, float maxVal, QString desc, QString tooltip)
{
	assert(!hasParameter(desc));
	FilterParameter p(name,desc,tooltip);
  p.fieldVal=defaultVal;
	p.fieldType=FilterParameter::PARABSPERC;
	p.min=minVal;
	p.max=maxVal;
	paramList.push_back(p);	
}
float		FilterParameterSet::getAbsPerc(QString name) const
{
	const FilterParameter *p=findParameter(name);
	assert(p);
	assert(p->fieldType == FilterParameter::PARABSPERC);
	return float(p->fieldVal.toDouble());
}
void FilterParameterSet::setAbsPerc(QString name, float newVal)
{
	FilterParameter *p=findParameter(name);
	assert(p);
	assert(p->fieldType == FilterParameter::PARABSPERC);
	p->fieldVal=QVariant(double(newVal));	
}
//--------------------
//对Enum类型参数的操作
void FilterParameterSet::addEnum (QString name, int defaultVal, QStringList values, QString desc, QString tooltip) {
	assert(!hasParameter(desc));
	FilterParameter p(name,desc,tooltip);
  p.fieldVal=defaultVal;
	p.fieldType=FilterParameter::PARENUM;
	p.enumValues = values;
	paramList.push_back(p);	
}

int FilterParameterSet::getEnum(QString name) const {
	const FilterParameter *p=findParameter(name);
	assert(p);
	assert(p->fieldType == FilterParameter::PARENUM);
	return float(p->fieldVal.toInt());
}

void FilterParameterSet::setEnum(QString name, int newVal)
{
	FilterParameter *p=findParameter(name);
	assert(p);
	assert(p->fieldType == FilterParameter::PARENUM);
	p->fieldVal=QVariant(int(newVal));	
}
//----------------------
//对FloatList类型参数的操作
void FilterParameterSet::addFloatList(QString name, QList<float> &defaultValue, QString desc, QString tooltip)
{
	assert(!hasParameter(desc));
	FilterParameter p(name,desc,tooltip);
	
	QList<QVariant> tempList;
	for(int i = 0; i < defaultValue.size(); ++i)
	{
		//if you put the float in directly int converts to a double which we do not want
		tempList.push_back(QVariant(QString().setNum(defaultValue.at(i), 'g', 12)));
		//qDebug() << "putting down " << QString().setNum(defaultValue.at(i), 'g', 12) ;
	}
	
	p.fieldVal = tempList;
	p.fieldType = FilterParameter::PARFLOATLIST;
	paramList.push_back(p);
}

QList<float> FilterParameterSet::getFloatList(QString name) const
{
	const FilterParameter *p = findParameter(name);
	assert(p);
	assert(p->fieldType == FilterParameter::PARFLOATLIST);
	
	QList<float> floatList;
	QList<QVariant> internalList = p->fieldVal.toList();
	for(int i = 0; i < internalList.size(); ++i)
		floatList.push_back(internalList.at(i).toString().toFloat());	
	
	return floatList;
}

void FilterParameterSet::setFloatList(QString name, QList<float> &newValue)
{
	FilterParameter *p = findParameter(name);
	assert(p);
	assert(p->fieldType == FilterParameter::PARFLOATLIST);
	
	QList<QVariant> tempList;
	for(int i = 0; i < newValue.size(); ++i)
	{
		tempList.push_back(QVariant(QString().setNum(newValue.at(i), 'g', 12)));
		//qDebug() << "insetfloatlist " << QVariant(QString().setNum(newValue.at(i), 'g', 12));
	}
	p->fieldVal = tempList;
}
//-------------------------

//对Mesh类型参数的操作
void FilterParameterSet::addMesh (QString name, MeshModel *defaultVal, QString desc, QString tooltip) {
	assert(!hasParameter(desc));
	FilterParameter p(name,desc,tooltip);
  p.pointerVal= defaultVal;
	p.fieldType=FilterParameter::PARMESH;
	paramList.push_back(p);	
}

//make the default the mesh that is at the given position in the mesh document
void FilterParameterSet::addMesh(QString name, int position,  QString desc, QString tooltip)
{
	assert(!hasParameter(desc));
	FilterParameter p(name,desc,tooltip);
	p.fieldVal = position;
	p.pointerVal = NULL;
	p.fieldType = FilterParameter::PARMESH;
	paramList.push_back(p);	
}

MeshModel * FilterParameterSet::getMesh(QString name) const {
	const FilterParameter *p=findParameter(name);
	assert(p);
	assert(p->fieldType == FilterParameter::PARMESH);
	return (MeshModel *)(p->pointerVal);
}

void FilterParameterSet::setMesh(QString name, MeshModel * newVal, int position)
{
	FilterParameter *p=findParameter(name);
	assert(p);
	assert(p->fieldType == FilterParameter::PARMESH);
	p->fieldVal = position;
	p->pointerVal= newVal;
}

/* ---- */
/* Dynamic Float Members*/
/* ---- */

void FilterParameterSet::addDynamicFloat(QString name, float defaultVal, float minVal, float maxVal, int changeMask, QString desc , QString tooltip )
{
	assert(!hasParameter(desc));
	FilterParameter p(name,desc,tooltip);
	assert(defaultVal<=maxVal);
	assert(defaultVal>=minVal);
  p.fieldVal=defaultVal;
	p.fieldType=FilterParameter::PARDYNFLOAT;
	p.min=minVal;
	p.max=maxVal;
	p.mask=changeMask;
	paramList.push_back(p);	
}

float FilterParameterSet::getDynamicFloat(QString name) const
{
	const FilterParameter *p=findParameter(name);
	assert(p);
	assert(p->fieldType == FilterParameter::PARDYNFLOAT);
	return float(p->fieldVal.toDouble());
}

void  FilterParameterSet::setDynamicFloat(QString name, float newVal)
{
	FilterParameter *p=findParameter(name);
	assert(p);
	assert(p->fieldType == FilterParameter::PARDYNFLOAT);
	p->fieldVal=QVariant(newVal);	
}

/* PAROPENFILENAME */

void FilterParameterSet::addOpenFileName(QString name, QString defaultVal, QString extension, QString desc, QString tooltip)
{
	assert(!hasParameter(desc));
	FilterParameter p(name,desc,tooltip);
	p.fieldVal = defaultVal; 
	p.fieldType = FilterParameter::PAROPENFILENAME;
	
	//add the extension to this unused variable because i think it is cleaner than adding another variable not used anywhere else
	p.enumValues.push_back(extension);
	
	paramList.push_back(p);
}

QString FilterParameterSet::getOpenFileName(QString name) const
{
	const FilterParameter *p = findParameter(name);
	assert(p);
	assert(p->fieldType == FilterParameter::PAROPENFILENAME);
	return p->fieldVal.toString();
}

void FilterParameterSet::setOpenFileName(QString name, QString newVal)
{
	FilterParameter *p = findParameter(name);
	assert(p);
	assert(p->fieldType == FilterParameter::PAROPENFILENAME);
	p->fieldVal = QVariant(newVal);	
}

/* PARSAVEFILENAME */

void FilterParameterSet::addSaveFileName(QString name, QString defaultVal, QString extension, QString desc, QString tooltip)
{
	assert(!hasParameter(desc));
	FilterParameter p(name,desc,tooltip);
	p.fieldVal = defaultVal; 
	p.fieldType = FilterParameter::PARSAVEFILENAME;
		
	//add the extension to this unused variable because i think it is cleaner than adding another variable not used anywhere else
	p.enumValues.push_back(extension);
	
	paramList.push_back(p);
}

QString FilterParameterSet::getSaveFileName(QString name) const
{
	const FilterParameter *p = findParameter(name);
	assert(p);
	assert(p->fieldType == FilterParameter::PARSAVEFILENAME);
	return p->fieldVal.toString();
}

void FilterParameterSet::setSaveFileName(QString name, QString newVal)
{
	FilterParameter *p = findParameter(name);
	assert(p);
	assert(p->fieldType == FilterParameter::PARSAVEFILENAME);
	p->fieldVal = QVariant(newVal);	
}
//-----------------------
//读取文件创建元素
QDomElement FilterParameter::createElement(QDomDocument &doc)
{
	QDomElement parElem = doc.createElement("Param");
	parElem.setAttribute("name",this->fieldName);
	switch (this->fieldType)
	{
		case FilterParameter::PARBOOL:
        parElem.setAttribute("type","Bool");
        parElem.setAttribute("value",this->fieldVal.toString());
		break;
    case FilterParameter::PARSTRING:
        parElem.setAttribute("type","String");
        parElem.setAttribute("value",this->fieldVal.toString());
    break;
    case FilterParameter::PARINT:
        parElem.setAttribute("type","Int");
        parElem.setAttribute("value",this->fieldVal.toInt());
    break;
    case FilterParameter::PARFLOAT:
        parElem.setAttribute("type","Float");
        parElem.setAttribute("value",this->fieldVal.toString());
    break;
    case FilterParameter::PARABSPERC:
        parElem.setAttribute("type","AbsPerc");
        parElem.setAttribute("value",this->fieldVal.toString());
        parElem.setAttribute("min",QString::number(this->min));
        parElem.setAttribute("max",QString::number(this->max));
    break;
    case FilterParameter::PARCOLOR:
        parElem.setAttribute("type","Color");
        parElem.setAttribute("rgb",this->fieldVal.toString());
    break;
    case FilterParameter::PARENUM:
		{
        parElem.setAttribute("type","Enum");
        parElem.setAttribute("value",this->fieldVal.toString());
        QStringList::iterator kk;
        for(kk = this->enumValues.begin();kk!=this->enumValues.end();++kk){
        	QDomElement sElem = doc.createElement("EnumString");
        	sElem.setAttribute("value",(*kk));
        	parElem.appendChild(sElem);
        }
		}
    break;
    case FilterParameter::PARMATRIX:
        {
				parElem.setAttribute("type","Matrix44");
        QList<QVariant> matrixVals = this->fieldVal.toList();
        for(int i=0;i<16;++i)
          parElem.setAttribute(QString("val")+QString::number(i),matrixVals[i].toString());
					}
    break;
    case FilterParameter::PARMESH:
    	  parElem.setAttribute(TypeName(), MeshPointerName());
    	  //this is the mesh's position in the mesh document that was used
    	  parElem.setAttribute(ValueName(),(this->fieldVal.toString()));
    break;
    case FilterParameter::PARFLOATLIST:
		{
    	parElem.setAttribute(TypeName(), FloatListName());
    	QList<QVariant> values = this->fieldVal.toList();
			for(int i=0; i < values.size(); ++i)
				{
					QDomElement listElement = doc.createElement(ItemName());
					listElement.setAttribute(ValueName(), values[i].toString());
					parElem.appendChild(listElement);
        }
		}
    break;
    case FilterParameter::PARDYNFLOAT:
    	  parElem.setAttribute(TypeName(), DynamicFloatName());
    	  parElem.setAttribute(ValueName(), this->fieldVal.toString());
    	  parElem.setAttribute(MinName(), QString::number(this->min));
    	  parElem.setAttribute(MaxName(), QString::number(this->max));
    	  parElem.setAttribute(MaskName(),QString::number(this->mask));
    break;
    case FilterParameter::PAROPENFILENAME:
    	  parElem.setAttribute(TypeName(), OpenFileNameName());
    	  parElem.setAttribute(ValueName(), this->fieldVal.toString());
    break;
    case FilterParameter::PARSAVEFILENAME:
        parElem.setAttribute(TypeName(), SaveFileNameName());
        parElem.setAttribute(ValueName(), this->fieldVal.toString());
		break;
		    case FilterParameter::PARPOINT3F:
				{
        QList<QVariant> pointVals = this->fieldVal.toList();
				parElem.setAttribute("type","Point3f");
        parElem.setAttribute("x",QString::number(pointVals[0].toDouble()));
        parElem.setAttribute("y",QString::number(pointVals[1].toDouble()));
        parElem.setAttribute("z",QString::number(pointVals[2].toDouble()));
				}
				break;
    default: assert(0);
    }
	return parElem;
	}
	//添加元素
void FilterParameter::addQDomElement(FilterParameterSet &par, QDomElement &np)
{
		QString name=np.attribute("name");
		QString type=np.attribute("type");

		qDebug("    Reading Param with name %s : %s",qPrintable(name),qPrintable(type));

		if(type=="Bool")    { par.addBool(name,np.attribute("value")!=QString("false")); return; }
		if(type=="Int")     { par.addInt(name,np.attribute("value").toInt()); return; }
		if(type=="Float")   { par.addFloat(name,np.attribute("value").toDouble()); return; }
		if(type=="String")  { par.addString(name,np.attribute("value")); return; }
		if(type=="AbsPerc") { par.addAbsPerc(name,np.attribute("value").toFloat(),np.attribute("min").toFloat(),np.attribute("max").toFloat()); return; }
		if(type=="Color")		{ par.addColor(name,QColor::QColor(np.attribute("rgb").toUInt())); return; }
		if(type=="Matrix44")
		{
		  Matrix44f mm;
			for(int i=0;i<16;++i)
					mm.V()[i]=np.attribute(QString("val")+QString::number(i)).toDouble();
			par.addMatrix44(name,mm);    
			return;                    
		}
		if(type=="Enum")
		{
			QStringList list = QStringList::QStringList();
			for(QDomElement ns = np.firstChildElement("EnumString"); !ns.isNull(); ns = ns.nextSiblingElement("EnumString")){
				list<<ns.attribute("value");
			}
			par.addEnum(name,np.attribute("value").toInt(),list);
			return;
		}
		
		if(type == MeshPointerName())  { par.addMesh(name, np.attribute(ValueName()).toInt()); return; }
		if(type == FloatListName())
		{
			QList<float> values;
			for(QDomElement listItem = np.firstChildElement(ItemName());
					!listItem.isNull();
					listItem = listItem.nextSiblingElement(ItemName()))
			{
					values.append(listItem.attribute(ValueName()).toFloat()); 
				}
			par.addFloatList(name,values);
			return;
		}
			
		if(type == DynamicFloatName())  { par.addDynamicFloat(name, np.attribute(ValueName()).toFloat(), np.attribute(MinName()).toFloat(), np.attribute(MaxName()).toFloat(), np.attribute(MaskName()).toInt()); return; }
		if(type == OpenFileNameName())  { par.addOpenFileName(name, np.attribute(ValueName())); return; }
		if(type == SaveFileNameName())  { par.addSaveFileName(name, np.attribute(ValueName())); return; }
		if(type=="Point3f") 
		{
			Point3f val;
			val[0]=np.attribute("x").toFloat();
			val[1]=np.attribute("y").toFloat();
			val[2]=np.attribute("z").toFloat();
			par.addPoint3f(name, val);  
			return; 
		}

		assert(0); // we are trying to parse an unknown xml element
}