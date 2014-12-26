import java.lang.System;
import java.util.*;
import java.io.*;

/**
 * Базовый класс для всех существ рода человеческого.
 */
class Person
{
	// Обычно по этим двум кодам идентифицируют человека 
	// в некотором пространственно-временном континууме.
	private String Fio;
	// Возраст, соответственно.
	private long Age;
	// ctor
	public Person(String Fio, long Age)
	{
		this.Fio = Fio;
		this.Age = Age;
	}

	// props
	public String getFio()
	{
		return Fio;
	}

	public void setFio(String Fio)
	{
		this.Fio = Fio;
	}

	public long getAge()
	{
		return Age;	
	}

	public void setAge(long Age)
	{
		this.Age = Age;
	}

	@Override
	public boolean equals(Object other)
	{
		boolean result = false;
		if (other instanceof Person) 
		{
			Person that = (Person) other;
			result = (this.getFio().equals(that.getFio())  && this.getAge() == that.getAge());
		}
		return result;
	}
}

/* 
 * Человек, встречает компьютер.
 */
class ItPerson extends Person
{
	/// Программист может быть разноплановой личностью, хоть ruby, хоть python
	private ArrayList<ProgrammerArea> Stage = new ArrayList<ProgrammerArea>();
	/// Сколько общий стаж работы
	private VerySimpleDate ItStage;
	
	/** Конструктор */
	public ItPerson(String Name, long Age, VerySimpleDate ItStage)
	{
		super(Name, Age);
		this.ItStage = ItStage;
	}
	
	/** Запрашиваем детальную информацию о стаже */
	public ArrayList<ProgrammerArea> getStageDetail()
	{
		return Stage;
	}
	
	/** Сколько лет человек работает в IT */
	public VerySimpleDate getItStage()
	{
		return ItStage;
	}

	/** Просто так берем и добавляем сет-скилов. 
	*   @param pa Область компетентности программиста.
	*/
	public void addPArea(ProgrammerArea pa)
	{
		Stage.add(pa);
	}
}


/*
 * Часть жизни программиста. посвященный какой-то области. Область скилов, это тоже скилл, но большой.
 */
class ProgrammerArea extends Skill
{
	// Набор умений в определнной области  
	private ArrayList<Skill> Skills = new ArrayList<Skill>();

	public ProgrammerArea(String Name, VerySimpleDate date)
	{
		super(Name, date);
	}
	
	//	
	public ArrayList<Skill> getSkills()
	{
		return Skills;
	}

	public void setSkills(ArrayList<Skill> Skills)
	{
		this.Skills = Skills;	
	}
		
	public void add(Skill sk)
	{
		this.Skills.add(sk);
	}
	@Override
	public String toString()
	{
		return new String("I own MegaSkill: " + this.getName() + " on time: " + this.getHowLong().getYear()  + " years and " + this.getHowLong().getMonth() + " months");
	}
}


/*
 * Технология для освоения (html, lamp, brainfuck and e.g.)
 */
class Skill
{
	private String Name;
	// стаж в технологии.
	private VerySimpleDate HowLong;

	// ctor
	public Skill(String Name, VerySimpleDate HowLong)
	{
		this.Name = Name;
		this.HowLong = HowLong;
	}

	// props
	public String getName()
	{
		return Name;
	}

	public void setName(String Name)
	{
		this.Name = Name;
	}

	public VerySimpleDate getHowLong()
	{
		return HowLong;
	}

	public void setHowLong(VerySimpleDate HowLong)
	{
		this.HowLong = HowLong;
	}
}


/*
 * Класс, для представления стажа работы.
 */
class VerySimpleDate
{
	private int year;
	private int month;

	public VerySimpleDate(int year, int month)
	{
		this.year	= year;
		this.month	= month;
	}

	public int getYear()
	{
		return year;
	}

	public void setYear(int year)
	{
		this.year = year;
	}

	public int getMonth()
	{
		return month;
	}

	public void setMonth(int month)
	{
		this.month = month;
	}

	static public String getFormattedStr(VerySimpleDate vsd)
	{
		String yearStr = "года";
		
		int tail = vsd.getYear()%10;
		
		if(tail >= 5 && tail <= 9 || tail == 0)
			yearStr = "лет";

		return new String(vsd.getYear() + " " + yearStr + " " + vsd.getMonth() + " месяцев");
	}
}

/** Класс, представление информации о некоторой работе */
class Job
{
	private String CompanyName;
	private String Vacantion;

	public String getCompanyName()
	{
		return CompanyName;
	}

	public void setCompanyName(String CompanyName)
	{
		this.CompanyName = CompanyName;		
	}

	public String getVacantion()
	{
		return Vacantion;
	}

	public void setVacantion(String Vacantion)
	{
		this.Vacantion = Vacantion;
	}
}

/** Класс, для инициализации сведений о работе из файла настроек */
class JobLoader
{
	/** Конструктор */
	public JobLoader(Job job, String fileName) throws IOException
	{
		FileInputStream fileInputStream = null;
		Properties properties = new Properties();

		try {
			fileInputStream = new FileInputStream(fileName);
			properties.load(fileInputStream);
			Enumeration enumeration = properties.keys();

			while (enumeration.hasMoreElements())
			{
				String key = enumeration.nextElement().toString();					
				String value = properties.getProperty(key);
				if(key.equals("CompanyName"))
					job.setCompanyName(value);
				else if(key.equals("Vacantion"))
					job.setVacantion(value);
			}
		}
		catch (FileNotFoundException e) {
			 new File(fileName).createNewFile();
			 e.getMessage();
		} catch (InvalidPropertiesFormatException e) {
		     e.getMessage();
		} catch (IOException e) {
			 e.getMessage();
		} finally {
			fileInputStream.close();
		}
	}
}

class Fixtures
{
	public void initData(ItPerson person, Job job)
	{
		if(person == null || job == null)
		{
			System.out.println("person or job is null");
			throw new NullPointerException();
		}
		// Опыт разработки C++ приложений - 5 лет и 3 месяца
		ProgrammerArea cppArea = new ProgrammerArea("C++ Programmer", new VerySimpleDate(5, 3));
		cppArea.add(new Skill("wxWidjets", cppArea.getHowLong()));
		cppArea.add(new Skill("boost", cppArea.getHowLong()));
		// etc...
		person.addPArea(cppArea);
		// Опыт разработки Java приложений - 9 мес.
		person.addPArea(new ProgrammerArea("Java Programmer", new VerySimpleDate(0, 9)));
		// Побочные освоенные технологии.
		person.addPArea(new ProgrammerArea("Others", new VerySimpleDate(6, 1)));

		try
		{
			JobLoader jl = new JobLoader(job, "job.ini");
		}
		catch(IOException e)
		{
			e.getMessage();
		}
	}
}


/**
 * Класс, который генерирует нужные фикстуры и выводит результат.
 */
public class Resume
{
	public static void main (String[] args)
	{
		// Заполним общую для всех людей информацию.
		Calendar calend = new GregorianCalendar();
		calend.set(1987, 9, 5); // ДР.
		Calendar rightNow = Calendar.getInstance();
		long yearsOfMe = rightNow.get(Calendar.YEAR) - calend.get(Calendar.YEAR);
		
		System.out.println("I'm " + yearsOfMe + " years old");
		
		ItPerson sp = new ItPerson("Борисов Дмитрий Вячеславович", yearsOfMe, new VerySimpleDate(6,1));		
		Job job = new Job();

		Fixtures fx = new Fixtures();
		fx.initData(sp, job);		
	
		String allStage = VerySimpleDate.getFormattedStr(sp.getItStage());

		// Вывод.
		System.out.println("Здравствуйте, " + job.getCompanyName()); 
		System.out.println("Меня зовут " + sp.getFio());
		System.out.println("В сфере IT я работаю уже " + allStage);
		System.out.println("Из этих " + allStage + " я был: ");
		
		// Оставим на остальные навыки на будущее, а пока извлечем его из списка при итерации по нему.
		ProgrammerArea otherArea = null;

		for(ProgrammerArea pa : sp.getStageDetail())
		{
			if(!"Others".equals(pa.getName()))
			{
				System.out.println("\t* " + pa.getName() + " ( " + VerySimpleDate.getFormattedStr(pa.getHowLong()) + " )");
				System.out.println("\tОсвоил технологии, библиотеки, навыки специфичные для этой области: ");
				printSkills(pa);
			}
			else
			{
				otherArea = pa;
			}
		}


		// Не забываем у нас есть и otherArea переменная, разбор которой мы оставили на потом. 
		System.out.println("Также за это время я получил множество знаний общих для IT-области: ");
		printSkills(otherArea);
	}

	static void printSkills(ProgrammerArea pa)
	{
		for(Skill sk : pa.getSkills())
		{
			System.out.println("\t\t- " + sk.getName());
		}
	}
}



