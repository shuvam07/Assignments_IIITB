import java.util.*;

class Tournament{
	
	List<Team> list;
	int roundNumber;
	String[] attr;
	int[] weights;
	HashMap<Integer,Integer> seen = new HashMap<Integer,Integer>();
	
	Tournament(int n,String[] attr,int[] weights){
		this.roundNumber = 1;
		this.attr = attr;
		this.weights = weights;
	}
	
	public void setTeamList(ArrayList<Team> teams) {
		this.list=teams;
	}
	
	@SuppressWarnings("unchecked")
	public String[] getSortedListOfAttrByWeight() {
		
		HashMap<String,Integer> m = new HashMap<String,Integer>();
		
		for(int i=0;i<this.attr.length;i++) {
			m.put(this.attr[i],this.weights[i]);
		}
		
		Object[] a = m.entrySet().toArray();
		
		Comparator<Object> cmp = new Comparator<Object>() {
		    public int compare(Object o1, Object o2) {
		        return ((HashMap.Entry<String, Integer>) o2).getValue()
		                   .compareTo(((HashMap.Entry<String, Integer>) o1).getValue());
		    }
		};
		    
		Arrays.sort(a, cmp);
		
		int i=0;
		for(Object e: a) {
			attr[i]=((HashMap.Entry<String,Integer>) e).getKey();
			i++;
		}
		
		return attr;
		
	}
	
	private List<String> getCurrentTeamsInTournament(){
		List<String> teams= new ArrayList<String> ();
		for(Team t: list) {
			teams.add(t.getName());
		}
		return teams;
	}
	
	private int getCurrentRoundNumber() {
		return roundNumber;
	}
	
	private void sortTeams() {
		
		Comparator<Team> cmp = new Comparator<Team>() {
	        public int compare(Team t1, Team t2) {
	            if(t1.getRandomVal()<t2.getRandomVal())
	            	return 1;
	            else return -1;
	        }
	    };
	    
	    Collections.sort(list, cmp);
		
	}
	
	private int compareTeams(Team t1,Team t2) {
		
		int[] attrVal1 = t1.getAttributeValues();
		int[] attrVal2 = t2.getAttributeValues();
		
		for(int i=0;i<attrVal1.length;i++) {
			if(attrVal1[i]>attrVal2[i]) {
				return 1;
			}
			else if(attrVal1[i]<attrVal2[i])
				return -1;
		}
		
		return 1;
	}
	
	private void playMatches() {
		
		List<Team> temp = new ArrayList<Team>();
		
		for(int i=0;i<list.size();i+=2) {
			Team team1 = list.get(i);
			Team team2 = list.get(i+1);
			System.out.println(team1.getName()+" vs "+team2.getName());
			if(this.compareTeams(team1,team2)>0) {
				temp.add(team1);
			}
			else {
				temp.add(team2);
			}
		}
		
		this.list =temp;
		
	}
	
	public void startTournament() {
				
		this.sortTeams();
		
		while(list.size()>=2) {
			
			System.out.println("ROUND "+this.getCurrentRoundNumber());
			playMatches();
			System.out.println("WINNER(S)");
			
			List<String> winners = this.getCurrentTeamsInTournament();
			for(String s: winners) {
				System.out.println(s);
			}
			System.out.println();
			this.roundNumber++;
			
		}	
	}
	
	public int getRandomValue() {
		
		
		Random rand = new Random();
		int n=0;
		while(seen.containsKey(n)) {
			n = rand.nextInt(100) + 1;
		}
		seen.put(n,1);
		return n;
	}
	
}

class Team{
	
	String name;
	int randomVal;
	int[] attrVal;
	
	Team(String name,int val,int[] attrVal){
		this.name= name;
		this.randomVal=val;
		this.attrVal = attrVal;
	}
	
	int getRandomVal() {
		return this.randomVal;
	}
	
	String getName() {
		return this.name;
	}
	
	int[] getAttributeValues() {
		return this.attrVal;
	}
}

public class Assign1 {

	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		
		System.out.print("Enter the number of teams: ");
		int n=sc.nextInt();
		
		String[] attr= {"Rank ", "Score " , "NumberOfTitlesWonPrev ", "Age" };
		
		int[] weights = new int[attr.length];
		
		System.out.println("Current Attributes for comparing winning team\n");
		for(int i=0;i<attr.length;i++) {
			System.out.print(attr[i]+" ");
		}
		System.out.println();
		
		System.out.println("\nAssign weights to each attribut(0 if not to be considered)");
		for(int i=0;i<attr.length;i++) {
			weights[i]=sc.nextInt();
		}
		
		System.out.println();
		
		Tournament t = new Tournament(n,attr,weights);
		
		ArrayList<Team> teams = new ArrayList<Team>();
		
		
		attr= t.getSortedListOfAttrByWeight();
		
		System.out.println("Enter details for each team");
		System.out.print("Name ");
		
		for(int i=0;i<attr.length;i++) {
			System.out.print(attr[i]+" ");
		}
		
		System.out.println();
		
		for(int i=0;i<n;i++) {
			
			int[] attrVal = new int[attr.length];
			
			String name = sc.next();
									
			for(int j=0;j<attr.length;j++) {
				attrVal[j]=sc.nextInt();
			}
			
			teams.add(new Team(name,t.getRandomValue(),attrVal));
		
		}
		
		t.setTeamList(teams);
		
		t.startTournament();
		
		sc.close();
		
	}

}
